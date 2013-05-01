
% testpercwalk.m %
% Generate spanning cluster (l-r spanning)
lx = 200;
ly = 200;
p = 0.59274;
p = [0.6,0.61,0.62,0.63,0.64,0.65];
%nstep = 1e5;
nstep = [100,500,1e3,5e3,1e4,5e4,1e5];
rr = zeros(1,length(nstep));
r2 = zeros(length(p),length(nstep));
nexperiments = 5e3;
hold all
leg = {};
for ind=1:length(p)
    leg{ind} = sprintf('p = %g',p(ind));
    P = p(ind);
    parfor ii=1:length(nstep)
        ii
        rr_tmp = 0;
        for l=1:nexperiments
            nnstep = nstep(ii)+1;
            ncount = 0;
            perc = [];
            while (size(perc ,1)==0)
                z=rand(lx,ly)<P;
                [lw,num]=bwlabel(z,4);
                perc_x = intersect(lw(1,:),lw(lx,:));
                perc = perc_x(perc_x~=0);
            end
%             s = regionprops(lw,'Area');
%             clusterareas = cat(1,s.Area);
%             maxarea = max(clusterareas);
%             i = find(clusterareas==maxarea);
            zz = lw == perc(1);
            % zz now contains the spanning cluster
            %imagesc(zz),axis equal ,axis tight
            rz = 1.0*zz;
            n = 1;
            while (n<=1)
                r = rand(nnstep ,1);
                [w,n] = percwalk(rz,r,0);
            end
            x = w(1,:);
            y = w(2,:);
            rr(1,ii) = rr(1,ii) + (x(end)-x(1))^2 + (y(end)-y(1))^2;
    %         rr_tmp = rr_tmp + (x(end)-x(1))^2 + (y(end)-y(1))^2;
        end
        rr(1,ii) = rr(1,ii)/nexperiments;
    end
    r2(ind,:) = rr(1,:);
    plot(log10(r2(ind,:)),log10(nstep))
    drawnow
end
%hold on,plot(y,x); hold off

% plot(log10(nstep),log10(rr(1,:)))
xlabel('log_{10}(N)')
ylabel('$$log_{10}(\langle r^2\rangle)$$','interpreter','latex')
legend(leg)