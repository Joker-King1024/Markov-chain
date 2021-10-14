function y = MyLowPassFilter(X_matrix,iCutOffFrequency,SampleTime)
    tmp = 1-exp((-2)*iCutOffrequency*pi*SampleTime)
    output=0
    
    for a = 1:size(X_matrix,1)
       output = output+(X_matrix(a,1)-output)*tmp
       y(a,1) = output
        
    end
end