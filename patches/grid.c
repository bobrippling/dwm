void
grid(Monitor *m) {
	int n;
	Client *c;

	snprintf(m->ltsymbol, sizeof m->ltsymbol,
			"HH%d", selmon->nmasters[selmon->curtag]);

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next))
		n++;

	ntile_arrange(m, nexttiled(m->clients), n / 2, n);
}
