int find_match
{
	int i,j;
	int plen, tlen; /* counters */
	/* string lengths */
	plen = strlen(p);
	tlen = strlen(t);
	for (i=0; i<=(tlen-plen); i=i+1) 
	{
		j=0;
		while ((j<plen) && (t[i+j]==p[j]))
			j = j+1;
		if (j == plen) return(i);
	}
	return(-1);
}
