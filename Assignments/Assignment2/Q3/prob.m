function [a] = prob(X,Y,cov)
	a = [X;Y]' * inv(cov) * [X;Y];
end