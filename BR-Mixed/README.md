# BR-Mixed
This folder contains a collection of ports for various BOFs and standalone tools, converted to the BRC4-compatible COFF syntax.
Credit for the original work is given to the respective authors in the sections below.

All COFFs in this folder support the argument `-h` which will print information about the available arguments and usage.
To compile all COFFs navigate to the `BR-Mixed` folder and type `make`.

This folder contains the following COFFs:
- [AAD PRT](#aad-prt)
- [EFS Trigger](#efs-trigger)
- [Get Azure Token](#get-azure-token)
- [Multi RDP](#multi-rdp)
- [PetitPotam](#petitpotam)
- [Session Enum](#session-enum)
- [Start WebClient](#start-webclient)
- [Delete Locked File (self delete)](#delete-locked-file-self-delete)
- [Cookie Monster](#cookie-monster)
- [SSPI UAC Bypass](#sspi-uac-bypass)

----

## AAD PRT
This COFF tries to fetch the local primary refresh token (PRT) on an EntraID joined device.

*Credits:*

[@wotwot563](https://x.com/wotwot563) and [@fastlorenzo](https://x.com/fastlorenzo)-> https://github.com/wotwot563/aad_prt_bof

```
[*] Usage: aadprt.o <nonce>
[*] <nonce>    (Optional argument) You can create a nonce using roadtx from ROADtools
```


## EFS Trigger
This COFF uses the `CreateFileA`-API to trigger the start of the Encrypted File System (EFS) service.

*Credits:*

[@0x64616e](https://x.com/0x64616e) -> https://gist.github.com/dadevel/903d78cc0dc8535063a80ba5b1405bcd

```
[*] Usage: efs_trigger.o <filepath>
[*] <filepath>    (Optional argument) Overwrites the default filepath of the temporary file
```


## Get Azure Token
This COFF uses Microsoft’s OAuth code flow with PKCE to authenticate a user via a browser, capture the returned authorization code on a local listener, and exchange it for Azure access tokens.

*Credits:*

[@freefirex2](https://x.com/freefirex2) -> https://github.com/trustedsec/CS-Remote-OPs-BOF/blob/main/src/Remote/get_azure_token/entry.c

```
[*] Usage: get_azure_token.o <client_id> <scope> <browser_id> <hint> <browser_path>
[*] <client_id>       Set the client id
[*] <scope>           Set the scope
[*] <browser_id>      Available Browser IDs:
                      0 - Edge
                      1 - Chrome
                      2 - Users Default Browser
                      3 - Other (Specify with <browser_path> arg)
[*] <hint>            (Optional - Set to 0 if not needed)
[*] <browser_path>    (Optional - Set to 0 if not needed)
```


## Multi RDP
This COFF patches certain code patterns in `termsrv.dll` of `svchost` processes, to allow multiple users to have an interactive desktop session on a desktop host.
This would allow you to for example RDP into a compromised host, even if another user is already connected to it.

*Credits:*

[@gentilkiwi](https://x.com/gentilkiwi) -> https://github.com/gentilkiwi/mimikatz

```
[*] Usage: multi_rdp.o
```


## PetitPotam
This COFF implements the PetitPotam attack via the MS-EFSRPC protocol.
The PetitPotam attack is a way to remotely coerce a Windows hosts into authenticating to other systems.

*Credits:*

[@Cneelis](https://x.com/Cneelis) -> https://github.com/outflanknl/C2-Tool-Collection/tree/main/BOF/PetitPotam

[@topotam77](https://x.com/topotam77) as original attack publisher.

```
[*] Usage: petitpotam.o <listener> <target>
[*] <listener>    Capture server ip or hostname
[*] <target>      Target server ip or hostname
```


## Session Enum
This COFF replicates the functionality of `qwinsta /server:<servername>` utilizing the largely undocumented Windows Station (WinSta) API.

*Credits:*

[@0xv1n](https://github.com/0xv1n) -> https://github.com/0xv1n/RemoteSessionEnum

```
[*] Usage: session_enum.o <targetName>
[*] <targetName>    Target server hostname (max. len: 20)
```


## Start WebClient
This COFF uses the windows event API to trigger the start of the WebClient service.

*Credits:*

[@Cneelis](https://x.com/Cneelis) -> https://github.com/outflanknl/C2-Tool-Collection/blob/main/BOF/StartWebClient/SOURCE/StartWebClient.c

```
[*] Usage: start_webclient.o
```


## Delete Locked File (self delete)
This COFF can delete locked files (like currently running PE files) using FileDispositionInfo flags.

*Credits:*

[@LloydLabs](https://x.com/LloydLabs) -> https://github.com/LloydLabs/delete-self-poc/

```
[*] Usage: delete_locked.o <filepath>
[*] <filepath>    Path to the locked file or 'self' for own process file
```


## Cookie Monster
This COFF will extract the WebKit Master Key and the App Bound Encryption Key for both Edge and Chrome, locate a browser process with a handle to the Cookies and Login Data files, copy the handle(s) and then copy the files to a specified location.


Since BRC4 does not have a native way to exfiltrate files as a COFF, you'll have to use BRC4s 'download' command to exfiltrate the created files.


Once the Cookies/Login Data file(s) are downloaded, the python decryption script of the original repository can be used to extract the included secrets! The Firefox module will parse the profiles.ini and locate where the logins.json and key4.db files are located and download them. A seperate github repo is referenced for offline decryption.

> **Info from the original repo!**
> Chrome & Edge 127+ Updates: new chromium browser cookies (v20) use the app bound key to encrypt the cookies.
> As a result, this makes retrieving the app_bound_encrypted_key slightly more difficult.
> Thanks to snovvcrash this process can be accomplished without having to escalate your privileges.
> The catch is your process must be running out of the web browser's application directory.
> i.e. must inject into Chrome/Edge or spawn a beacon from the same application directory as the browser.

Decrypt Firefox Cookies and Stored Credentials: https://github.com/lclevy/firepwd

Decrypt Chrome and Edge Cookies and Stored Credentials: https://github.com/KingOfTheNOPs/cookie-monster/blob/main/decrypt.py

*Credits:*

[@KingOfTheNOPs](https://x.com/kingofthenops) -> https://github.com/KingOfTheNOPs/cookie-monster

```
[*] Usage: cookie_monster.o [ chrome || edge || system <Local State File Path> <PID> || firefox || chrome-cookies <PID> || chrome-login-data <PID> || edge-cookies <PID> || edge-login-data <PID> ] [<Output Dir>] [--cookie-only] [--key-only] [--login-data-only]

[*] Available modes:
    chrome               looks at all running processes and handles, if one matches chrome.exe it copies the handle to cookies and then copies the file to the CWD
    edge                 looks at all running processes and handles, if one matches msedge.exe it copies the handle to cookies and then copies the file to the CWD
    system               Decrypt chromium based browser app bound encryption key without injecting into browser. Requires path to Local State file and PID of a user process for impersonation
    firefox              looks for profiles.ini and locates the key4.db and logins.json file
    chrome-cookies       using the provided chrome PID to look for the specified process with a handle to cookies is known, specifiy the pid to duplicate its handle and file
    chrome-login-data    using the provided chrome PID to look for the specified process with a handle to Login Data is known, specifiy the pid to duplicate its handle and file
    edge-cookies         using the provided edge PID to look for the specified process with a handle to cookies is known, specifiy the pid to duplicate its handle and file
    edge-login-data      using the provided edge PID to look for the specified process with a handle to Login Data is known, specifiy the pid to duplicate its handle and file

[*] Available Options:
    --key-only           only retrieve the app bound encryption key. Do not attempt to download the Cookie or Login Data files.
    --cookie-only        only retrieve the Cookie file. Do not attempt to download Login Data file or retrieve app bound encryption key.
    --login-data-only    only retrieve the Login Data file. Do not attempt to download Cookie file or retrieve app bound encryption key.

[*] Examples (example output dir is 'C:\temp\'):
    cookie-monster chrome "C:\temp\"
    cookie-monster edge "C:\temp\"
    cookie-monster system "C:\Users\<USER>\AppData\Local\<BROWSER>\User Data\Local State" <PID> "C:\temp\"
    cookie-monster firefox "C:\temp\"
    cookie-monster chrome-cookies <PID> "C:\temp\"
    cookie-monster chrome-login-data <PID> "C:\temp\"
    cookie-monster edge-cookies <PID> "C:\temp\"
    cookie-monster edge-login-data <PID> "C:\temp\"
```


## SSPI UAC Bypass
This COFF forges a token from a fake network authentication though SSPI Datagram Contexts.
It will then impersonate the forged token and use a CreateSvcRpc call (by @x86matthew) to create a new SYSTEM service.

*Credits:*

[@icyguider](https://x.com/icyguider) -> https://github.com/icyguider/UAC-BOF-Bonanza/tree/main/SspiUacBypass

[@splinter_code](https://twitter.com/splinter_code) -> for original research

[@x86matthew](https://twitter.com/x86matthew) -> for CreateSvcRpc research

```
[*] Usage: sspi_uac_bypass.o <filepath>
[*] <filepath>    full path to the executable that will be launched with elevated privileges
```