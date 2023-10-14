// WARNING: May include multiple copies of the same point if duplicates are included in input
// Returns convex hull in clockwise order

struct pt {
    ld x, y;
};

bool cmp(pt a, pt b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<pt>& a) {
    if (sz(a) == 1)
        return;

    sort(all(a), &cmp);
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.pb(p1);
    down.pb(p1);
    FOR(i, 1, sz(a)) {
        if (i == sz(a) - 1 || cw(p1, a[i], p2)) {
            while (sz(up) >= 2 && !cw(up[sz(up)-2], up[sz(up)-1], a[i]))
                up.pop_back();
            up.pb(a[i]);
        }
        if (i == sz(a) - 1 || ccw(p1, a[i], p2)) {
            while(sz(down) >= 2 && !ccw(down[sz(down)-2], down[sz(down)-1], a[i]))
                down.pop_back();
            down.pb(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < sz(up); i++)
        a.push_back(up[i]);
    for (int i = sz(down) - 2; i > 0; i--)
        a.push_back(down[i]);
}
