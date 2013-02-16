void moveresize(const Arg *arg) {
	XEvent ev;
	Monitor *m = selmon;
	const int *param = arg->v;

	if(!(m->sel && arg && arg->v))
		return;
	/*
	 * if monitor->tag[monitor->selectedtag]->has_arrange_function
	 * and the selected client isn't floating...
	 */
	if(m->lt[m->sellt]->arrange && !m->sel->isfloating)
		m->sel->isfloating = True;

	resize(m->sel,
			m->sel->x + param[0],
			m->sel->y + param[1],
			m->sel->w + param[2],
			m->sel->h + param[3],
			True);

	arrange(m);

	while(XCheckMaskEvent(dpy, EnterWindowMask, &ev));
}

void jumpto(const Arg *arg) {
	Monitor *m = selmon;
	XEvent ev;

	if(!m->sel || !arg)
		return;

	{
#define LEFT   (m->wx)
#define RIGHT  (m->wx + m->ww - m->sel->w)
#define TOP    (m->wy)
#define BOTTOM (m->wy + m->wh - m->sel->h)
		struct
		{
			int x, y;
		} jumps[] = {
			{ LEFT,  TOP    },
			{ RIGHT, TOP    },
			{ LEFT,  BOTTOM },
			{ RIGHT, BOTTOM }
		};

		if(!(0 <= arg->i && arg->i < LENGTH(jumps)))
			return;

		if(m->lt[m->sellt]->arrange && !m->sel->isfloating)
			m->sel->isfloating = True;

		resize(m->sel,
				jumps[arg->i].x,
				jumps[arg->i].y,
				m->sel->w,
				m->sel->h,
				True);

		arrange(m);

		while(XCheckMaskEvent(dpy, EnterWindowMask, &ev));
	}
}
