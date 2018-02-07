clc;
clear;
eig_vec1 = [1; 5];
eig_val1 = 10;
eig_vec2 = [-5; 1];
eig_val2 = 2;
lambda = [eig_val1 0; 0 eig_val2];
U = [eig_vec1 eig_vec2];
R = U * lambda * inv(U);
no_of_points = 200;
points = randn(no_of_points,2) * R;
% points = repmat([0 0],no_of_points,1) + randn(no_of_points,2)*chol(R);
x_avg = mean(points(:,1));
y_avg = mean(points(:,2));
points_avg = [(points(:,1) - x_avg) , (points(:,2) - x_avg)];
covariance = [mean(points_avg(:,1).^2) 				 mean(points_avg(:,1).*points_avg(:,2));
			  mean(points_avg(:,1).*points_avg(:,2)) mean(points_avg(:,2).^2)];

plot(points(:,1),points(:,2),'.');
axis equal;
hold on;
[pca_line1,pca_line2] = PCA(points,covariance);
x = min(points(:,1)):0.5:max(points(:,1));
plot(x,pca_line1(1)*x+pca_line1(2),'-r');
plot(x,pca_line2(1)*x+pca_line2(2),'-y');

[eig_line1,eig_line2] = PCA(points,R);
plot(x,eig_line1(1)*x,'-black');
plot(x,eig_line2(1)*x,'-green');

legend({'generated points','principal component1','principal component2','given eigen vector1','given eigen vector2'},'location','northwest');
xlabel('X');
ylabel('Y');
title('Solution 2');
hold off;