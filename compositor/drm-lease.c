/*
 * Copyright © 2021 IGEL Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "drm-lease.h"

#include <libweston/libweston.h>

int get_drm_lease(struct dlm_lease **drm_lease, const char *drm_lease_name) {
	if (!drm_lease_name)
		return -1;

	int drm_fd;
	struct dlm_lease *lease = dlm_get_lease(drm_lease_name);
	if (lease) {
		drm_fd = dlm_lease_fd(lease);
		if (drm_fd < 0)
			dlm_release_lease(lease);
	}
	if (drm_fd < 0)
	    weston_log("Could not get DRM lease %s\n", drm_lease_name);

        *drm_lease = lease;
	return drm_fd;
}

void release_drm_lease(struct dlm_lease *lease) {
	if (lease)
		dlm_release_lease(lease);
}


