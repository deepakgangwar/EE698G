function [H] = Pose_to_rot(X)
	X(4:6) = X(4:6)*pi/180;
	R_x = [1	0	0;
	   0	cos(X(4))	sin(X(4));
	   0	-sin(X(4))	cos(X(4))];
	R_y = [cos(X(5))	0	-sin(X(5));
		   0	1	0;
		   sin(X(5))	0	cos(X(5))];
	R_z = [cos(X(6))	sin(X(6))	0;
		   -sin(X(6))	cos(X(6))	0;
		   0	0	1];
	R = R_z'*R_y'*R_x';
	T = [X(1),X(2),X(3)];
	H = [R  T' ; 0 0 0  1];
end