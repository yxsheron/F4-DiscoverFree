/*
 * ls.c
 *
 * Created on: Jul 16, 2012
 *     Author: Ekawahyu Susilo
 *
 * Copyright (c) 2012, Chongqing Aisenke Electronic Technology Co., Ltd.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of the copyright holder.
 * 
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include "system.h"
#include "dirent.h"

#ifdef CONFIG_SYSTEM_HAVE_LS
#include "ff.h"

int ls_app(int argc, char **argv)
{
	DIR dir;
	FILINFO fno;
	FRESULT rc;
	//struct dirent *dirp;

	if (argc == 1)
		rc = f_opendir(&dir, ".");
	else
		rc = f_opendir(&dir, argv[1]);

	for (;;) {
		rc = f_readdir(&dir, &fno);		// Read a directory item
		if (rc || !fno.fname[0]) break;	// Error or end of dir
		if (fno.fattrib & AM_DIR)
			printf("   <dir>  %s\n", fno.fname);
		else
			printf("%8lu  %s\n", fno.fsize, fno.fname);
	}

	//f_closedir(&dir); // FIXME no implementation of f_close(), implement closedir instead

	//closedir(dp);

	return 0;
}

int ls_help(int argc, char **argv)
{
	printf("usage: ls [dirname]\n");

	return 0;
}
#endif
