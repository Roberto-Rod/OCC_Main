function Lorentzian_conv()

lorentz = zeros(2000, 1);

for i = 1:2000
    lorentz(i) = 20^2/((i-1000)^2+20^2) + 0.5 * 20^2/((i-1500)^2+20^2);
end

w = conv(lorentz, lorentz(800:1200), 'same');
w = w / max(w);

x = 1:2000;
plot(x, lorentz, x, w);

end
