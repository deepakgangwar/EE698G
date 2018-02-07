function [ inliers ] = Ransac_3d( points,required_probability,inlier_fraction,S,threshold )
%RANSAC_3D removes outliers from the 3d point cloud

n = log(1-required_probability)/log(1-inlier_fraction^S);
n = ceil(n);
point_count = size(points);
rand_index = randperm(point_count(1),S*n);
for i=1:n
    x1 = points(rand_index(i),1);
    x2 = points(rand_index(i+1),1);
    x3 = points(rand_index(i+2),1);
    y1 = points(rand_index(i),2);
    y2 = points(rand_index(i+1),2);
    y3 = points(rand_index(i+2),2);
    z1 = points(rand_index(i),3);
    z2 = points(rand_index(i+1),3);
    z3 = points(rand_index(i+2),3);
    %plane eq z=ax+by+c
    a = ((z1-z2)*(y2-y3) - (z2-z3)*(y1-y2))/((x1-x2)*(y2-y3) - (x2-x3)*(y1-y2));
    b = ((z1-z2)*(x2-x3) - (z2-z3)*(x1-x2))/((y1-x2)*(x2-x3) - (y2-y3)*(x1-x2));
    c = z3 - a*x3 - b*y3;
    k = 1;
    for j=1:point_count
        if (points(j,1)*a + b*points(j,2) - points(j,3) + c)/(a^2+b^2+1)^0.5 <= threshold
            inliers(k,:) = points(j,:);
            k = k+1;
        end
    end
end

end