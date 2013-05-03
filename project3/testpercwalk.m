
% testpercwalk.m %
% Generate spanning cluster (l-r spanning)
lx = 200;
ly = 200;

% p = [0.6,0.61,0.62,0.63,0.64,0.65];
p = [0.59,0.58,0.57,0.56,0.55];

nstep = [100,500,1e3,5e3,1e4,5e4,1e5];
r2 = zeros(length(p),length(nstep));
nexperiments = 5e3;
% nexperiments = 1;
hold all
leg = {};

for ind=1:length(p)
    rr = zeros(1,length(nstep));
    P = p(ind);
    ind
    for ii=1:length(nstep)
        nnstep = nstep(ii)+1;
        rr_tmp  = 0;
        parfor l=1:nexperiments
            ncount = 0;
%             perc = [];
%             while (size(perc ,1)==0)
            z=rand(lx,ly)<P;
            [lw,num]=bwlabel(z,4);
%                 perc_x = intersect(lw(1,:),lw(lx,:));
%                 perc = perc_x(perc_x~=0);
%                 perc = find(perc_x>0);
%             end
            s = regionprops(lw,'Area');
            clusterareas = cat(1,s.Area);
            maxarea = max(clusterareas);
            i = find(clusterareas==maxarea);
            zz = lw == max(i);
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
            rr_tmp = rr_tmp + (x(end)-x(1))^2 + (y(end)-y(1))^2;
        end
%         rr(1,ii) = rr(1,ii)/nexperiments;
        rr(1,ii) = rr_tmp/nexperiments;
    end
    r2(ind,:) = rr(1,:);
    leg{ind} = sprintf('p = %g',p(ind));
    plot(log10(nstep),log10(r2(ind,:)))
    drawnow
end
%hold on,plot(y,x); hold off

% plot(log10(nstep),log10(rr(1,:)))
xlabel('log_{10}(N)')
ylabel('$$log_{10}(\langle r^2\rangle)$$','interpreter','latex')
legend(leg)