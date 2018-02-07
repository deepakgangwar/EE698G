function [particles,p_w] = generate_particles(x,Np,P)

% Input
% x - initial starting pose
% P - covariance
% Np - number of particles

% Output
% p_w - weights of particles
% particles- each particle represents a potential pose of the robot at any time t

% particles = repmat(x,Np,1) + randn(Np,3)*chol(P);
particles = mvnrnd(x,P,Np);
p_w = ones(Np,1);
p_w = p_w./Np;
particles = particles';
end


 