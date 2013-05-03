% exwalk.m

lx = 64*4;
ly = 64*4;
% p = 0.585;
p = 0.59275;
L = 2.^(3:9);
M_SC = zeros(1,length(L));
nsamples = 500;

for q = 1:length(L)
    lx = L(q);
    ly = lx;
    for sample =1:nsamples
        ncount = 0;
        perc = [];
        while (isempty(perc))
           ncount = ncount + 1;
           if ncount >1000
               return
           end
           z = rand(lx,ly)<p;
           [lw,num] = bwlabel(z,4);
           perc_x = intersect(lw(1,:),lw(lx,:));
           perc_y = intersect(lw(:,1),lw(:,ly));
           perc = perc_x(perc_x ~= 0);
        end
        % s = regionprops(lw,'Area');
        % clustersize = cat(1,s.Area);
        % maxarea = max(clustersize);
        % i = find(clustersize == maxarea);
        zz = lw==perc(1);

    %zz now contains the spanning cluster
    % imagesc(zz); %visualize spanning cluster

        %Run walk on this cluster

        [l,r] = walk(zz);
        zzz = l.*r; % Find points where both l and r are nonzero
        M_SC(1,q) = M_SC(1,q) + length(zzz(zzz~=0));
        zadd = zz + zzz;
    end
end


plot(log10(L),log10(M_SC(1,:)))

% 
% subplot(2,2,1), imagesc(zz);
% subplot(2,2,2), imagesc(zadd);
% subplot(2,2,3), imagesc(zzz);
% subplot(2,2,4), imagesc(1+r>0);
% figure(4)
% imagesc(l)
% title('left')
% figure(5)
% imagesc(r)
% title('right')