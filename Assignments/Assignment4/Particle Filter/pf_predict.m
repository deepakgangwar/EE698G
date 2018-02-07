 function [x,particles]=pf_predict(particles,v,g,Q,dt,p_w)
 
 % Input
 % particles
 % v,g - the actual controls i.e velocity and orientation
 % Q - covariance of noisy controls
 % p_w - weigths
 % dt - timestep
 
 
% Output
% x - The pose given by the most weighted particle. 
 

% Propogate particles via motion model.

n = size(particles,2);

for i = 1:n
	[V,G] = add_control_noise(v,g,Q,1);
	particles(1,i) = particles(1,i) + V * dt * cos(G + particles(3,i));
	particles(2,i) = particles(2,i) + V * dt * sin(G + particles(3,i)); 
	particles(3,i) = pi_to_pi(particles(3,i) + G);
end
[value index] = max(p_w);
x = particles(:,index);
 
 
 
 
 
 
 end
 
    
    
    
    
    
    
    
    
