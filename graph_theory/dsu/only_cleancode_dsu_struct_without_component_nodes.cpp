struct DSU{
	
	int cc=0;
	vector<int>parent,sz;
	
	DSU(int n){
		parent.assign(n+1,0),sz.assign(n+1,0);
		for(int i=1;i<=n;i++){
			cc++;
			parent[i]=i;
			sz[i]=1;
		}
	}
	
	int get_super(int u){
		if(u==parent[u])return u;
		return parent[u]=get_super(parent[u]);
	}
	
	bool is_connected(int u,int v){
		u=get_super(u);
		v=get_super(v);
		return u==v;
	}
	
	bool merge(int u, int v){
		u=get_super(u);
		v=get_super(v);
		
		if(u==v) return 0;
		
		cc--;
		
		if(sz[u]<sz[v]) swap(u,v);
		
		parent[v]=u;
		sz[u]+=sz[v];
		
		return 1;
	}
	
	
};
