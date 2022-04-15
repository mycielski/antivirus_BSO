% AVBSO(1)
% Tomasz Mycielski
% April 2022

# NAME
**avbso** - write this to pass this class

# SYNOPSIS
**avbso** [file_with_hashes] [path_to_scan]

# DESCRIPTION
**avbso** scans files and calculates their SHA256 checksums. If a file's digest matches one found in the hashes database (passed as the first cli argument of the program) that file is flagged as malicious and moved to quarantine. Malicious files have their x permission unset. You can exit the program while it is running by passing a SIGINT (Ctrl+C). It will exit gracefully.

# HASHING ALGORITHM
File digest is generated with the SHA 256 algorithm provided by the OpenSSL library. The choice to use this algorithm comes from my experience with VirusTotal, as it is the type of hash VT accepts for lookups. The digests are generated chunk-after-chunk (without loading whole file to memory) so even large files can be handled.

# HASHES DATABASE
When using the program a file with hashes must be provided. The format of the file must be ASCII text, one hash per line, no whitespace.

# DIRECTORY TRAVERSAL
The program can take a path of a file to scan but also a path to a directory. If the latter is the case then the program will recursively search through the directory and its subdirectories to find all files in them. There are limitations to this however. Anything in /proc, /dev will be skipped, and so will a /swapfile, if it exists. **Warning:** the program *does not* follow symlinks!

Everything in directories /proc, /dev, and the /swapfile won't be scanned. There is currently no way of overriding this mechanism, short of recompiling the program.

# QUARANTINE DIRECTORY
**avbso** uses /var/tmp/quarantine to store malicious files. The reasoning behind this choice is that once a malicious file is discovered then the user might want to preserve it for forensics purposes. By default systemd based distros will keep the contents of quarantine for 30 days. It is more than enough time to decide what should be done with each of the files. 
In /var/tmp/quarantine a new directory is created for each scan. The new directory is named yyyy-mm-dd_hh-mm-ss to indicate when the scan took place. If a scan took less than a second then the program will wait until a second passed before exiting. That is done to prevent launching two scans which would generate the same timestamp. Inside of a scan-directory are soft symlinks to malicious files. The names of the symlinks are the files' SHA256 digests. If the scan-directory is empty then it means **no** malicious files were found.

# QUARANTINE MECHANISM
Upon discovery, a malicious file is stripped of its permissions (apart from read). That way it can be investigated but any code it may contain won't be executed.

# BUILDING
Before building the program make sure you have **cmake** available on your system. **avbso** comes with a handy build script. Once you clone the repository to your machine just run ```build.sh``` and the resulting binary will be placed in ```build/release/avbso```. You may also clean up any and all artifacts by running ```cleanup.sh```.
During building **pandoc** is used for rendering the manpage in GNU Troff format. This step is not essential, especially since **avbso** comes with a pre-rendered manpage. If you would like to only render the manpage you can do so by running doc/build_manpage.sh.

# CODE STYLE
**clang-format --style=Google** was used to format the source. A tiny bit of effort was made for the code to conform to Google's style guide.

# DOCUMENTATION
All the documentation is available as a manpage. You can see it by running ```man doc/manpage```. Alternatively, you can use your markdown renderer of choice with ```doc/manpage.md```.

# EXAMPLES
The program comes with an example. Run ```avbso example/hashes ./``` to see it work on a dummy malicious file and a simple list of hashes.
All the testing of this program was done on a live Arch Linux system with 5.17.2-arch3-1.

# POSSIBLE IMPROVEMENTS
## Hash storage
Currently the program accepts hashes as strings. This is inefficient, since hashes are just 256 bit numbers. If the hashes were to be treated as numbers it would allow for optimized storage and searching.

## CLI
The program could also take some CLI options. For example it could feature a "dry run" option which would scan files and inform if any malicious ones were found, but not quarantine them.

## Symlinks handling
Currently symlinks are being ignored to prevent loops or unexpected growth of scan times. A more robust antivirus solution would handle symlinks the way its user explicitly states it should be done.

## Code style
I am not a programmer. And it shows.

# BUGS
No known bugs.

# AFTERWORD
This project was great and I enjoyed doing it. I haven't used C++ before but I really like it now. I learned new things about Linux, which is marvelous.
