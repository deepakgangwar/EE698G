function  [p_w] = compute_weights(particles,p_w,z,idf,R,lm)

 % Compute weights of particles.
 
 % Input 
 % particles
 % p_w - current weights
 % z - observations
 % idf - landmark identifier.
 % R - covariance of noisy observations
 % lm - set of landmarks
  
 % Output
 % p_w - new weights
 
size_idf = size(idf);
n = size(particles,2);
if numel(idf) == 0
	return;
else
	for i=1:size_idf
		for j = 1:n
			z_predicted = zeros(size(z,1),n);
			l = lm(:,idf(i));
			z(2,i) = pi_to_pi(z(2,i));
			dist = sqrt((particles(1,j)-l(1))^2+(particles(2,j)-l(2))^2);
			z_predicted(:,j) = [dist;	pi_to_pi(atan2(l(2)-particles(2,j),l(1)-particles(1,j)) - particles(3,j))];
			% z(:,i) = add_observation_noise(z(:,i),R,1); 
			err = z(:,i) - z_predicted(:,j);
			p_w(j) = p_w(j)/abs(err(1)*err(2));
		end
	end
end

p_w = p_w/sum(p_w);

end


