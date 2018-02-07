function [ inliers ] = Ransac( points,required_probability,inlier_fraction,S,threshold )
%RANSAC removes outliers from the 2d points

n = log(1-required_probability)/log(1-inlier_fraction^S);
n = ceil(n);
point_count = size(points);
rand_index = randperm(point_count(1),S*n);
for i=1:n
    x1 = points(rand_index(i),1);
    x2 = points(rand_index(i+1),1);
    y1 = points(rand_index(i),2);
    y2 = points(rand_index(i+1),2);
    m = (y2 - y1)/(x2 - x1);
    c = y1 - m*x1;
    k = 1;
    for j=1:point_count
        if (points(j,1)*m - points(j,2) + c)/(m^2+1)^0.5 <= threshold
            inliers(k,:) = points(j,:);
            k = k+1;
        end
    end
end

end

