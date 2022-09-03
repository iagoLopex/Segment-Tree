#include <iostream>
#include <ctsdio>

struct no{
	int maior;
	int menor;
};

int custo[100100];
no seg[400100];

no func(no a, no b){
	no c;
	c.maior = std::max(a.maior, b.maior);
	c.menor = std::min(a.menor, b.menor);
	return c;
}

// n*log n
no build(int left, int right, int t){
	
	if(left == right){
		seg[t]={custo[left],custo[left]};
		return seg[t];    
	}
	int mid = ((left+right)>>1);
	return seg[t] = func( build(left,mid,2*t) , build(mid+1, right, 2*t+1) );
}

// log n
no query(int i, int j, int left, int right, int t){
	if(left>=i && right<=j){//all in
		
		return seg[t];
	}
	if(right<i || j<left){//all out
		return {-10000,10000};
	}
	
	int mid = ((left+right)>>1);
	return func( query(i, j, left, mid, 2*t), query(i, j, mid+1, right, 2*t+1));
}

no update(int x, int pos, int left, int right, int t){
	if(pos<left || pos>right){//all out
		return seg[t];
	}
	if(left==right && left==pos){//i find the element, i am in the leaves
		custo[pos]=x;
		return seg[t]={x,x};
	}
	int mid = ((left+right)>>1);
	return seg[t] = func( update(x, pos, left, mid, 2*t), update(x, pos, mid+1, right, 2*t+1) );
}

int main(){
	
	int n, token, o, id, id2, p;
	while(scanf("%d",&n)!=EOF){
		
		for(int i=0; i<n; i++){
			scanf("%d",&custo[i]);
		}
		build(0, n-1, 1);
		
		scanf("%d",&o);
		for(int i=0; i<o; i++){
			
			scanf("%d", &token);
			if(token == 1){//update
				
				scanf("%d %d",&id, &p);
				update(p, id-1, 0, n-1, 1);
			}
			else{//query
				
				scanf("%d %d",&id, &id2);
				no h = query(id-1, id2-1, 0, n-1, 1); 
				printf("%d\n", h.maior-h.menor);
			}
		}
		//delete(seg);
		//delete(custo);
	}
}
