function [R,T] = ICP(scan1,scan2,iters,R_init,T_init,max_tresh)
	R = R_init;
	T = T_init;

	R_temp = R;
	T_temp = T;

	temp_scan = [scan2;ones(size(scan2(1,:)))];
	H_temp = [R,T ; zeros(size(R(1,:))),1];
	H = H_temp;
	for i = 1:iters
		temp_scan = R*scan2+repmat(T,1,size(scan2,2));
		[P Q] = correspondance(temp_scan,scan1,max_tresh);
		P_zero_mean = (P - repmat(mean(P)',[1,size(P,1)])');
		Q_zero_mean = (Q - repmat(mean(Q)',[1,size(Q,1)])');
		[U,~,V] = svd(P_zero_mean' * Q_zero_mean);
		% [U,~,V] = svd((P - repmat(mean(P)',[1,size(P,1)])')' * (Q - repmat(mean(Q)',[1,size(Q,1)])'));
		% temp_scan = H_temp * temp_scan;
		% R = U * V';
		% T = mean(Q)' - R * mean(P)';
		% H_temp = [R,T ; zeros(size(R(1,:))),1];
		% H = H * H_temp;

		% H_temp = [R_temp,T_temp ; zeros(size(R(1,:))),1];
		R_temp = U * V';
		T_temp = mean(Q)' - R_temp * mean(P)';
		T = T - inv(R)*T_temp;
		R = R * R_temp;

	end
	% R = H(1:2,1:2);
	% T = H(1:2,3);
end




















