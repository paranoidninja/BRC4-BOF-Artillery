# BR-Situational-Awareness

This repository contains a collection of BRC4 BOFs ported from [CS-Situational-Awareness-BOF](https://github.com/trustedsec/CS-Situational-Awareness-BOF). The repository also provides a list correlating CS BOFs to pre-existing BRC4 Commands. While the core logic of the BOFs remain contant, some modifications have been made to provide more comprehensive outputs, along with  revelant usage instructions.

Most BOFs support the `-h`/`--help`/`/?` flag to print help

| CS-Situational-Awareness-BOF | BRC4 Equivalent | Usage | Description |
|:-----------------------------| :-----------| :---------------|:--------------------------------------------|
| aadjoininfo                  | BOFF Implemented                               | `aadjoininfo` | Print AAD/Entra ID Join Info |
| arp                          | `arp` command                                  | `arp` | List ARP entries for all network interfaces on the current host |
| cacls                        | acl C:\Path\to\file                            | Closely resembled by the `acl` command | List ACL for an object. While the CS BOF supports wild cards, the BRC4 command does not|
| dir                          | BOFF Implemented!                              | dir [directory] [/s]               | List files in a directory. Supports wildcards (e.g. "C:\Windows\S*") unlike the BRC4 `ls` command |
| driversigs                   | BOFF Implemented!                              | driversigs            | Enumerate installed services Imagepaths to check the signing cert against known AV/EDR vendors |
| enum_filter_driver           | BOFF Implemented!                              | enum_filter_driver [opt:computer] | Enumerate filter drivers. |
| enumLocalSessions            | Closely implemented by `local_session` command | `local_session` | Enumerate currently attached user sessions both local and over RDP |
| env                          | Can be achieved by `get` command               | `get env` | List process environment variables |
| findLoadedModule             | BOFF Implemented                               | `findLoadedModule [modulepart] [opt:procnamepart]` | findLoadedModule [modulepart] [opt:procnamepart]	Find what processes *modulepart* are loaded into, optionally searching just *procnamepart* | 
| get_password_policy          | Closely implemented by the `get_password_policy` command | `get_password_policy` |Get target server or domain's configured password policy and lockouts|
| get_session_info | Can be achieved by using a conjection of `local_session` and `query_session` command | `local_session`; `query_session` | Get information about current user session | 
| ipconfig | `ipstats` command | `ipstats` | Print IP interfaces |
| ldapsearch | Implemented by the Sentinel scene | See Docs | Execute LDAP queries |
| listdns | closely resembled by `dnscache` | `dnscache` | Print local storage of DNS records |
| listmods | `list_modules` | `list_modules <PID>` | Lists all the DLLs loaded in the current process or a target process. | 
| listpipes | Can be achieved by `ls` command  | `ls \\.\pipe\` | List named pipes |
| locale | BOFF Implemented! | `locale` | List system locale language, locale ID, date, time, and country |
| resources | BOFF Implemented! | `resources` | List memory usage and available disk space on the primary hard drive |
