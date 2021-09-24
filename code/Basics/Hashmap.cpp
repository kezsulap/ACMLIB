//Include Miscellaneous/SplitMix.cpp
const ull SALT = 2693721898232345818ull;
sim>typename enable_if<is_integral<c>::value,ull>::type my_hash(c x){
	if(sizeof(c)>8) return splitmix64((ull)x^SALT)^splitmix64((ull)(x>>64)^SALT);
	return splitmix64(x^SALT);
}
template<size_t N>ull my_hash(const bitset<N>&x){
	return splitmix64(hash<bitset<N>>()(x)^SALT);
}
sim,class n>ull my_hash(const pair<c,n>&);
sim,class n>using gyv=c;
sim>gyv<ull,typename c::value_type>my_hash(const c&x){
	ull o=SALT;
	for(auto&d:x)o=splitmix64(o^my_hash(d));
	return o;
}
sim,class n>ull my_hash(const pair<c,n>&x){return splitmix64(my_hash(x.first))^my_hash(x.second);}
sim>struct my_hasher{size_t operator()(const c&o)const{return my_hash(o);}};
#ifdef LOCAL
sim, class m> using _un0rDer3d_M4P=unordered_map<c,m,my_hasher<c>>;
sim> using _un0rDer3d_5et = unordered_set<c, my_hasher<c>>;
#else
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
// can use gp_hash_table instead of cc_hash_table, depends on specifics of the problem which will be faster
sim, class m> struct _un0rDer3d_M4P : public cc_hash_table<c,m,my_hasher<c>>{bool count(const c&x)const{return this->find(x) != this->end();}};
sim> using _un0rDer3d_5et = _un0rDer3d_M4P<c, null_type>;
#endif
#define unordered_map _un0rDer3d_M4P
#define unordered_set _un0rDer3d_5et
