//Maximum Cardinality Search
while (cur) {
  p[cur] = h[nww];
  rnk[p[cur]] = cur;
  h[nww] = nxt[h[nww]];
  lst[h[nww]] = 0;
  lst[p[cur]] = nxt[p[cur]] = 0;
  tf[p[cur]] = true;
  for (vector<int>::iterator it = G[p[cur]].begin(); it != G[p[cur]].end();
       it++)
    if (!tf[*it]) {
      if (h[deg[*it]] == *it) h[deg[*it]] = nxt[*it];
      nxt[lst[*it]] = nxt[*it];
      lst[nxt[*it]] = lst[*it];
      lst[*it] = nxt[*it] = 0;
      deg[*it]++;
      nxt[*it] = h[deg[*it]];
      lst[h[deg[*it]]] = *it;
      h[deg[*it]] = *it;
    }
  cur--;
  if (h[nww + 1]) nww++;
  while (nww && !h[nww]) nww--;
}

//Checking if a sequence is a perfect elimination ordering
jud = true;
for (int i = 1; i <= n; i++) {
  cur = 0;
  for (vector<int>::iterator it = G[p[i]].begin(); it != G[p[i]].end(); it++)
    if (rnk[p[i]] < rnk[*it]) {
      s[++cur] = *it;
      if (rnk[s[cur]] < rnk[s[1]]) swap(s[1], s[cur]);
    }
  for (int j = 2; j <= cur; j++)
    if (!st[s[1]].count(s[j])) {
      jud = false;
      break;
    }
}
if (!jud)
  printf("Imperfect\n");
else
  printf("Perfect\n");
