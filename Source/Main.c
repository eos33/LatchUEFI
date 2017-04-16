#include <Uefi.h>

#include "latch.h"
#include "Main.h"

EFI_STATUS MainApplication(int argc, char *argv){
	init(AppId, AppSecret);

	switch(argv[1]){
		case "-h", "--help":
			Print(L"Latch Standalone Application: Version %i\n", version);
			Print(L"Port made by @lordsergio\n");
			Print(L"\n");
			Print(L"Usage: Latch.efi [Options] [Arguments]\n");
			Print(L"\t -h, --help \t Print this menu\n");
			Print(L"\t -a, --accountid \t Read the Account ID for check the lock\n");
			Print(L"\t -p, --pair \t Read the pair code to return the Account ID\n");
			break;
		case "-p", "--pair":
			char *response = pair(argv[2]);
			if(response == TRUE){
				Print(L"Your AccountID is %s\n", response);
				Print(L"Execute this app with a AccountID Directly.\n");

				return EFI_SUCCESS;
			} else {
				Print(L"The Pair code is wrong, please, reinsert the code.\n");
				return EFI_HTTP_ERROR;
			}
			break;
		case "-a", "--accountid":
			int response = status(argv[2]);
			if(response == TRUE){
				Print(L"The boot check is passed, booting the System OS.\n");
				return EFI_SUCCESS;
			} else {
				Print(L"The System Boot has locked, please, unlock the system for boot.\n");
				return EFI_SECURITY_VIOLATION;
			}
			break;
		default:
			Print(L"Select a argument for boot the application.\n");
			return EFI_INVALID_PARAMETER;
	}
}
