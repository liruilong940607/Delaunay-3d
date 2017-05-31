# include<iostream>
# include<stdio.h>
# include<stdlib.h>
# include<vector>
# include<array>
# include"Vector3.h"
# include<time.h>
# include"convhull.h"

using namespace std;

int main() {
	srand((unsigned)time(0));

	Vector3 s[6] = {Vector3(1,0,0),Vector3(0,1,0),
		            Vector3(0,0,1),Vector3(0,0,0),
					Vector3(0.3f,0.3f,0.3f),
	                Vector3(0.3f,0.2f,0.1f)};

	QuickHull3D QH( s, 6 ); 

    vector<array<Vector3,3>>K = QH.Quick_Hull3D();

	// print K
	printf("%d\n", K.size());
	for( int i=0; i<K.size(); i++ ) {
		for( int j=0; j<3; j++ ) 
			printf("(%f, %f, %f), ", K[i][j].X, K[i][j].Y, K[i][j].Z );
		printf("\n");
	}



	return 0;
}
