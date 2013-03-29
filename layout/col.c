void
col(Monitor *m) {
	int x, y, h, w, mw, nm;
	unsigned int i, n;
	Client *c;

	snprintf(m->ltsymbol, sizeof m->ltsymbol, "||%d",
			selmon->pertag->nmasters[selmon->pertag->curtag]);

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	c = nexttiled(m->clients);
	nm = m->pertag->nmasters[selmon->pertag->curtag];
	if(nm > n)
		nm = n;
	/* master */
	if(nm > 0) {
		mw = (n == nm) ? m->ww : m->mfact * m->ww;
		w = mw / nm;
		x = m->wx;
		for(i = 0; i < nm; i++, c = nexttiled(c->next)) {
			resize(c, x, bh /* bar height */, w, m->wh, False);
			/*x = c->x + WIDTH(c);*/
			x += WIDTH(c);
		}
		n -= nm;
	} else {
		mw = 0;
	}
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
