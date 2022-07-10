#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h> // IWYU pragma: keep
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "RbFileManager.h"
#include "RbSettings.h"
#include "StringUtilities.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#ifdef _WIN32
#	include <dirent.h>
#   include <unistd.h>
#   include <windows.h>
#   include <shlwapi.h>
#else
#	include <dirent.h>
#   include <unistd.h>
#endif


namespace fs = boost::filesystem;

namespace RevBayesCore
{

path append_to_stem(const path& p, const std::string& s)
{
    return p.parent_path() / ( p.stem().string() + s + p.extension().string() );
}

/** Default constructor, creating a file manager object with the file
 path equal to the current (default) directory and an empty file name */
RbFileManager::RbFileManager( void )
{
    fs::path p = fs::current_path() / "";
    p.make_preferred();

    file_path = p.parent_path().string();
    file_name = "";
    full_file_name = p.string();
}


/** Constructor with full file/directory name */
RbFileManager::RbFileManager(const std::string &fn)
{
    fs::path p = fn;

    if (not p.is_absolute())
        p = fs::current_path() / p;

    p.make_preferred();

    file_path = p.parent_path().string();
    file_name = p.filename().string();
    full_file_name = p.string();
}


/** Constructor with path name and file/directory name */
RbFileManager::RbFileManager(const std::string &pn, const std::string &fn)
{
    fs::path p = fs::path(pn) / fs::path(fn);

    if (not p.is_absolute())
        p = fs::current_path() / p;

    p.make_preferred();

    file_path = p.parent_path().string();
    file_name = p.filename().string();
    full_file_name = p.string();
}


/**
 * Recursively create the directories which are present in the full file name.
 */
void RbFileManager::createDirectoryForFile( void )
{
    fs::create_directories( fs::path( full_file_name ).parent_path() );
}

/** Get line while safely handling cross-platform line endings.
 *  Modified from: https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
 *
 * @param[in] is stream from which to read
 * @param[out] t string to store the line read
 *
 * @return the input stream
 * */
std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
            case '\n':
                return is;
            case '\r':
                if(sb->sgetc() == '\n')
                    sb->sbumpc();
                return is;
            case EOF:
                // Also handle the case when the last line has no line ending
                if(t.empty())
                    is.setstate(std::ios::eofbit);
                return is;
            default:
                t += (char)c;
        }
    }
}


/**
 * Portable code to get a full path by expanding the user home directory.
 *
 * @param path relative path
 * @return full path including user home directory
 */
std::string expandUserDir(std::string path)
{
    if ( !path.empty() && path[0] == '~')
    {
        char const* home = getenv("HOME");
        
        if (home or ((home = getenv("USERPROFILE"))))
        {
            path.replace(0, 1, home);
        }
    }
    else if ( path.empty() == false )
    {
        char const *hdrive = getenv("HOMEDRIVE"), *hpath = getenv("HOMEPATH");
        if ( hdrive != NULL )
        {
# ifdef _WIN32
            path = std::string(hdrive) + hpath + "\\" + path;
# else
            path.replace(0, 1, std::string(hdrive) + hpath);
# endif
        }
        
    }
    
    return path;
}


/** Format an error exception string for problems specifying the file/path name
 * @param[out] errorStr string to store the formatted error
*/
void RbFileManager::formatError(std::string& errorStr)
{
    
    bool file_nameProvided    = isFileNamePresent();
    bool isfile_nameGood      = testFile();
    bool isDirectoryNameGood = testDirectory();
    
    if ( file_nameProvided == false && isDirectoryNameGood == false )
    {
        errorStr += "Could not read contents of directory \"" + getFilePath() + "\" because the directory does not exist";
    }
    else if (file_nameProvided == true && (isfile_nameGood == false || isDirectoryNameGood == false))
    {
        errorStr += "Could not read file named \"" + getFileName() + "\" in directory named \"" + getFilePath() + "\" ";
        if (isfile_nameGood == false && isDirectoryNameGood == true)
        {
            errorStr += "because the file does not exist";
        }
        else if (isfile_nameGood == true && isDirectoryNameGood == false)
        {
            errorStr += "because the directory does not exist";
        }
        else
        {
            errorStr += "because neither the directory nor the file exist";
        }
    }
    
}


std::string RbFileManager::getFileExtension( void ) const
{
    std::vector<std::string> tokens;
    StringUtilities::stringSplit(file_name,".",tokens);
    return tokens[tokens.size()-1];
}


const std::string& RbFileManager::getFileName( void ) const
{
    return file_name;
}


std::string RbFileManager::getFileNameWithoutExtension( void ) const
{
    std::vector<std::string> tokens;
    StringUtilities::stringSplit(file_name,".",tokens);
    std::string name = "";
    
    for (size_t i = 0; i < tokens.size()-1; ++i)
    {
        if(i > 0) name += ".";
        name += tokens[i];
    }
    
    return name;
}


const std::string& RbFileManager::getFilePath( void ) const
{
    return file_path;
}


const std::string& RbFileManager::getFullFileName( void ) const
{
    return full_file_name;
}


/** Get absolute file path from file_path
 * @return absolute path
 */
std::string RbFileManager::getFullFilePath( void ) const
{
    
    std::string fullfile_path = file_path;
    
    // check if file_path is relative or absolute
    // add current working path only if relative
#   ifdef RB_XCODE
    if ( file_path.size() > 0 && getPathSeparator()[0] != file_path[0] )
#    else
    boost::filesystem::path tmp_file = boost::filesystem::path(file_path);
    if ( tmp_file.is_absolute() == false )
#    endif
    {        
        fullfile_path = (fs::current_path() / file_path ).make_preferred().string();
    }
    
    return fullfile_path;
    
}


/** Get the last path component of full_file_name
 * @note any trailing path separator is removed, so x/y/z/ will return z
 * @return last path component
 */
std::string RbFileManager::getLastPathComponent( void )
{
    
    std::string tmp = full_file_name;
    if ( tmp[tmp.size()-1] == getPathSeparator()[0] )
    {
        tmp = tmp.substr(0,tmp.size()-1);
    }
    return RevBayesCore::getLastPathComponent( tmp );
}


/** Get the last path component of a path
 * @note any trailing path separator is NOT removed, so x/y/z/ will return an empty string
 * @param s input path
 * @return last path component
 */
std::string getLastPathComponent(const std::string& s)
{
    auto ss = fs::path(s).filename().string();
    if (ss == ".")
        ss == "";
    return ss;
}


std::string getPathSeparator( void )
{
#   ifdef _WIN32
    return "\\";
#   else
    return "/";
#   endif
}


/** Removes the last path component from a path
 * @note any trailing path separator is NOT removed, so x/y/z/ will return x/y/z
 * @return string without the last path component
 */
std::string getStringByDeletingLastPathComponent(const std::string& s)
{
    return fs::path(s).parent_path().make_preferred().string();
}


/** Checks whether full_file_name is a path to an existing directory */
bool RbFileManager::isDirectory( void ) const
{
    return fs::is_directory(full_file_name);
}


/** Tests whether a directory is present (and is a directory)
 * @param mp path to check
 * @return result of the test
 */
bool isDirectoryPresent(const std::string &mp)
{
    return fs::is_directory(mp);
}


/** Checks whether the path given by file_path + file_name is a path to an existing file */
bool RbFileManager::isFile( void ) const
{
    auto f = fs::path(file_path) / fs::path(file_name);
    return fs::is_regular_file(f) and not fs::is_directory(f);
}


/** Checks whether the file name is non-empty */
bool RbFileManager::isFileNamePresent(void) const
{
    
    if ( file_name == "" )
    {
        return false;
    }
    
    return true;
}


/** Checks whether a file passed in as its path and file name components is present (and a file)
 * @param mp file path - if empty, set to the working directory
 * @param mf file name
 * @return whether the file exists
*/
bool isFilePresent(const std::string &mp, const std::string &mf)
{ 
    auto f = fs::path(mp) / fs::path(mf);
    
    return fs::is_regular_file(f) and not fs::is_directory(f);
}

/** Checks whether a file passed in as its full path is present (and is a file)
 * @param fn full file path
 * @return whether the file exists
*/
bool isFilePresent(const std::string &fn)
{
    fs::path f = fn;

    return fs::is_regular_file(f) and not fs::is_directory(f);
}

void RbFileManager::setFileName(std::string const &s)
{
    file_name = s;
}


void RbFileManager::setFilePath(std::string const &s)
{
    file_path = s;
#	ifdef _WIN32
    StringUtilities::replaceSubstring(file_path,"/","\\");
#   endif
    
}

/** Fills in a vector with the names of the files in the directory file_path
 *
 * @param[out] sv vector to store the names
 * @param[in] recursive whether to list recursively, default true
 *
 * @return true
*/
bool RbFileManager::setStringWithNamesOfFilesInDirectory(std::vector<std::string>& sv, bool recursive)
{
    
    return RevBayesCore::setStringWithNamesOfFilesInDirectory(file_path, sv, recursive);
}


/** Fills in a vector with the names of the files in a directory
 *
 * @param[in] dirpath path to the directory to be listed
 * @param[out] sv vector to store the names
 * @param[in] recursive whether to list recursively, default true
 *
 * @return true
*/
bool setStringWithNamesOfFilesInDirectory(const std::string& dirpath, std::vector<std::string>& sv, bool recursive)
{
        
    DIR* dir = opendir( dirpath.c_str() );
    if (dir)
    {
        struct dirent* entry;
        while ( (entry = readdir( dir )) )
        {
            struct stat entryinfo;
            std::string entryname = entry->d_name;
            std::string entrypath = dirpath + getPathSeparator() + entryname;
            
            bool skip_me = false;

#ifdef _WIN32
            if (stat( entrypath.c_str(), &entryinfo )) {
              // if this returned a non-zero value, something is wrong
              skip_me = true;
            }
#else
            if (!lstat( entrypath.c_str(), &entryinfo ))
            {
                
                // avoid recursing into symlinks that point to a directory above us
                if ( S_ISLNK( entryinfo.st_mode ) ) {
                    char *linkname = (char*) malloc(entryinfo.st_size + 1);
                    ssize_t r = readlink(entrypath.c_str(), linkname, entryinfo.st_size + 1);
                    if (r < 0 || r > entryinfo.st_size) {
                        // error
                        skip_me = true;
                    } else {
                        linkname[entryinfo.st_size] = '\0';
                        if (strspn(linkname, "./") == entryinfo.st_size) {
                            // this symlink consists entirely of dots and dashes and is likely a reference to a directory above us
                            skip_me = true;
                        } else {
                            // replace entryinfo with info from stat
                            if ( stat( entrypath.c_str(), &entryinfo ) ) {
                                // if this returned a non-zero value, something is wrong
                                skip_me = true;
                            }
                        }
                    }
                    free(linkname);
                }

            } else {
              // if this returned a non-zero value, something is wrong
              skip_me = true;
            }
#endif

            if (!skip_me) {

                if (entryname == "..")
                {
                    ;
                }
                else if (entryname == "." || entryname[0] == '.')
                {
                    ;
                }
                else if ( recursive == true && S_ISDIR( entryinfo.st_mode ) )
                {
                    setStringWithNamesOfFilesInDirectory( entrypath, sv );
                }
                else
                {
                    sv.push_back( entrypath );
                }
            }
            
        }
        
        closedir( dir );
    }
    
    // make sure that the file names are sorted
    std::sort(sv.begin(), sv.end());
    
    return true;
}


/** Tests whether the directory specified in the object exists
 * @return true if file_path exists
 */
bool RbFileManager::testDirectory(void)
{   
    return isDirectoryPresent(file_path);
}


/** Tests whether the file specified in the object exists
 * @return true if file_path + file_name exists
 */
bool RbFileManager::testFile(void)
{   
    return isFilePresent(file_path, file_name);
}
}
