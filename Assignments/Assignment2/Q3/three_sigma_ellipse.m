function [points] = three_sigma_ellipse(data,mu,cov)
	[theta r] = meshgrid(min(data(:,1)):0.1:max(data(:,1)),min(data(:,2)):0.1:max(data(:,2)));
	mesh_size = size(theta);
	points = mu;
	for i = 1:mesh_size(1)
		for j = 1:mesh_size(2)
			if prob(theta(i,j) - mu(1) , r(i,j) - mu(2) , cov) <= 3
				points = [points,[theta(i,j);r(i,j)]];
			end
		end
	end
end