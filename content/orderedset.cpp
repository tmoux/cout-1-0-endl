#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/* order_of_key(k), how many elements < k */
/* find_by_order(k), k'th element (from 0) */
