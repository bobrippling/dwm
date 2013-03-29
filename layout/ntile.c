void
ntile_arrange(Monitor *m, Client *c, int nm, int n) {
	unsigned int i;
	int x, y, h, w, mw;

	if(nm > n)
		nm = n;
	/* master */
	if(nm > 0) {
		mw = m->mfact * m->ww;
		h = m->wh / nm;
		if(h < bh)
			h = m->wh;
		y = m->wy;
		for(i = 0; i < nm; i++, c = nexttiled(c->next)) {
			resize(c, m->wx, y, (n == nm ? m->ww : mw) - 2 * c->bw,
			       ((i + 1 == nm) ? m->wy + m->wh - y : h) - 2 * c->bw, False);
			if(h != m->wh)
				y = c->y + HEIGHT(c);
		}
		n -= nm;
	} else
		mw = 0;
	if(n == 0)
		return;
	/* tile stack */
	x = m->wx + mw;
	y = m->wy;
	w = m->ww - mw;
	h = m->wh / n;
	if(h < bh)
		h = m->wh;
	for(i = 0; c; c = nexttiled(c->next), i++) {
		resize(c, x, y, w - 2 * c->bw,
		       ((i + 1 == n) ? m->wy + m->wh - y : h) - 2 * c->bw, False);
		if(h != m->wh)
			y = c->y + HEIGHT(c);
	}
}
