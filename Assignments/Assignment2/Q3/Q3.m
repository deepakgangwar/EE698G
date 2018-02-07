clc;
clear;
load('data.mat');
mu = [1,3]';
cov_data = [0.5 0; 0 1];

figure, plot(data(:,1),data(:,2),'.');
axis equal;
hold on;
points = three_sigma_ellipse(data,mu,cov_data);
plot(points(1,:),points(2,:),'.g');
legend('points','3-sigma error region');
xlabel('theta');
ylabel('r');
title('Polar data and 3 sigma error region');
hold off;

jacobian = [-mu(2)*sin(mu(1)) cos(mu(1));mu(2)*cos(mu(1)) sin(mu(1))];
data_euclidean = [data(:,2) .* cos(data(:,1)),data(:,2) .* sin(data(:,1))];
figure, plot(data_euclidean(:,1),data_euclidean(:,2),'.');
axis equal;
hold on;
mu = mean(data_euclidean)';
points = three_sigma_ellipse(data_euclidean,mu,cov(data_euclidean));
plot(points(1,:),points(2,:),'.g');
points = three_sigma_ellipse(data_euclidean - 0.05,mu,jacobian*cov_data*jacobian');%points in the 3sigma region will not overlap it is ensured by 0.05
plot(points(1,:),points(2,:),'.r');
legend('points','3-sigma error region','3-sigma error region by linearization');
xlabel('X');
ylabel('Y');
title('Euclidean data and 3 sigma error regions');
hold off;