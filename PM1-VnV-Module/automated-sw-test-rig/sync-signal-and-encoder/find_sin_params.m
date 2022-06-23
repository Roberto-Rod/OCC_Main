function retval = find_sin_params (t, y, f) %t=time, y=signal, f=frequency
  yu = max(y); % Max of y
  yl = min(y); % Min of y
  yr = (yu-yl); % Range of y
  yz = y-yu+(yr/2); % Y zeroed
  ym = mean(y); % Estimate offset

  fit = @(b,t)  b(1).*(sin(2*pi*t.*b(2) + 2*pi*b(3))) + b(4);    % Function to fit

  if f > 0 %Assuming the frequency has been specified, run a quicker routine:
    
    %First, fit phase shift
    fcn = @(b) sum((fit([0.5*yr;  f;  b;  ym],t) - y).^2); % Least-Squares cost function
    phase_shift_1 = fminbnd(fcn, 0, 1);
    %Next, fit mean
    fcn = @(b) sum((fit([0.5*yr;  f;  phase_shift_1;  b],t) - y).^2); % Least-Squares cost function
    mean_1 = fminbnd(fcn, -2, 2);
    %Next, fit amplitude
    fcn = @(b) sum((fit([b;  f;  phase_shift_1;  mean_1],t) - y).^2); % Least-Squares cost function
    amplitude_1 = fminbnd(fcn, 0.01, 2);

    %The ultimate solution is:
    s = [amplitude_1; f;  phase_shift_1;  mean_1];

  else %Or, if the frequency has been defined...
      
    zt = t(yz .* circshift(yz,[1 0]) <= 0);  % Find zero-crossings
    period = 2*max(diff(zt));                % Estimate period
    frequency = 1/period;                    % Estimate frequency

    %First, fit phase shift
    fcn = @(b) sum((fit([0.5*yr;  frequency;  b;  ym],t) - y).^2); % Least-Squares cost function
    phase_shift_1 = fminbnd(fcn, 0, 1);
    %Next, fit frequency
    fcn = @(b) sum((fit([0.5*yr;  b;  phase_shift_1;  ym],t) - y).^2); % Least-Squares cost function
    frequency_1 = fminbnd(fcn, 0.8*frequency, 1.2*frequency);
    %Next, fit phase shift again
    fcn = @(b) sum((fit([0.5*yr;  frequency_1;  b;  ym],t) - y).^2); % Least-Squares cost function
    phase_shift_2 = fminbnd(fcn, 0, 1);
    %Next, fit frequency again
    fcn = @(b) sum((fit([0.5*yr;  b;  phase_shift_2;  ym],t) - y).^2); % Least-Squares cost function
    frequency_2 = fminbnd(fcn, 0.8*frequency, 1.2*frequency);
    frequency_2 = round((frequency_2-200)/1000)*1000 + 200-1000; % Round to nearest 200 + i * 1000Hz
    for frequency_3 = frequency_2:1000:frequency_2+10000
      %Next, fit phase shift again
      fcn = @(b) sum((fit([0.5*yr;  frequency_3;  b;  ym],t) - y).^2); % Least-Squares cost function
      phase_shift_3 = fminbnd(fcn, 0, 1);
      %Next, fit mean
      fcn = @(b) sum((fit([0.5*yr;  frequency_3;  phase_shift_3;  b],t) - y).^2); % Least-Squares cost function
      mean_1 = fminbnd(fcn, -2, 2);
      %Next, fit amplitude
      fcn = @(b) sum((fit([b;  frequency_3;  phase_shift_3;  mean_1],t) - y).^2); % Least-Squares cost function
      amplitude_1 = fminbnd(fcn, 0.01, 2);

      s = [amplitude_1; frequency_3;  phase_shift_3;  mean_1];
      
      error = fcn(s);
      if frequency_3 == frequency_2
        best_error = error;
        best_frequency = frequency_3;
      elseif error < best_error
        best_error = error;
        best_frequency = frequency_3;
      end        
    end

    frequency_3 = best_frequency;
    %Next, fit phase shift again
    fcn = @(b) sum((fit([0.5*yr;  frequency_3;  b;  ym],t) - y).^2); % Least-Squares cost function
    phase_shift_3 = fminbnd(fcn, 0, 1);
    %Next, fit mean
    fcn = @(b) sum((fit([0.5*yr;  frequency_3;  phase_shift_3;  b],t) - y).^2); % Least-Squares cost function
    mean_1 = fminbnd(fcn, -2, 2);
    %Next, fit amplitude
    fcn = @(b) sum((fit([b;  frequency_3;  phase_shift_3;  mean_1],t) - y).^2); % Least-Squares cost function
    amplitude_1 = fminbnd(fcn, 0.01, 2);

    %The ultimate solution is:
    s = [amplitude_1; frequency_3;  phase_shift_3;  mean_1];

  end
  %tp = linspace(min(t),max(t));
  %figure
  %plot(t,y,'b',  t,fit(s,t), 'r')
  retval = s;

endfunction
