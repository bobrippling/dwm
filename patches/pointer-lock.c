void
pointerlock(const Arg *a)
{
	if(a->i){
		if(!selmon->sel)
			return;
		if(XGrabPointer(dpy, selmon->sel->win, False, MOUSEMASK,
				GrabModeAsync, GrabModeAsync,
				selmon->sel->win, None, CurrentTime) != GrabSuccess)
			fprintf(stderr, "dwm: XGrabPointer() failed\n");
	}else
		XUngrabPointer(dpy, CurrentTime);
}
