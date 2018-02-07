function [mu,sigma,K] = Kalman(A,B,C,Z,u,Rt,Qt,mu,sigma)
	%%Kalman Filter

	%prediction
	mu = A * mu + B * u;
	sigma = A * sigma * A' + Rt;

	%correction
	K = sigma * C' * pinv(C * sigma * C' + Qt);
	mu = mu + K * (Z - C * mu);
	sigma = (eye(size(sigma)) - K * C) * sigma;
end