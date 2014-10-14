  function [selectedRows, selectedColumns, maxProbabilities] = selectBestTopicPair(numTopics, matrix, topicIndexes, clusterAssignment, mapTopics, originalNumTopics, alpha, minProbability, maxCohesion, transitionMatrix, iter, outputDir, stationaryProbabilities, irreducibleMatrix, leavinProbability, meanNumberOfLinks)

      matrixSize = numTopics * numTopics;
      dirtyTopics = zeros(numTopics);
      maxProbabilities = zeros(numTopics);
      selectedRows = zeros(numTopics);
      selectedColumns = zeros(numTopics);
      temporaryMatrix = zeros(numTopics, numTopics);

      outputFileUnicityName = strcat(outputDir,'unicity', num2str(iter), '_', num2str(numTopics), '.txt');
      outputFileUnicity = fopen(outputFileUnicityName, 'w');
      
      outputFileCohesionName = strcat(outputDir,'cohesion', num2str(iter), '_', num2str(numTopics), '.txt');
      outputFileCohesion = fopen(outputFileCohesionName, 'w');
      
      outputFileDeltaCohesionName = strcat(outputDir,'deltaCohesion', num2str(iter), '_', num2str(numTopics), '.txt');
      outputFileDeltaCohesion = fopen(outputFileDeltaCohesionName, 'w');
      
      outputFileDeltaUnicityName = strcat(outputDir,'deltaUnicity', num2str(iter), '_', num2str(numTopics), '.txt');
      outputFileDeltaUnicity = fopen(outputFileDeltaUnicityName, 'w');

      %zera diagonais para evitar de retorná-las
      for i=1:numTopics,

	  t1 = topicIndexes(i);
	  if [ t1 > originalNumTopics ]
		t1 = mapTopics(t1 - originalNumTopics);
	  end
         topic1 = i;

	  for j=(i+1):numTopics,

		t2 = topicIndexes(j);
		if [ t2 > originalNumTopics ]
			t2 = mapTopics(t2 - originalNumTopics);
		end

                topic2 = j;

                if[ topic2 == topic1 ]
                  continue
                end

		resultingCluster = clusterAssignment(t1,:) + clusterAssignment(t2,:);
		numFactors = sum(resultingCluster);
                meanFactors = numFactors / 2.0;

                minFactors = sum(clusterAssignment(t1,:));
                maxFactors = sum(clusterAssignment(t2,:));

                lenTopic1 = sum(clusterAssignment(t1,:));
                lenTopic2 = sum(clusterAssignment(t2,:));
                
                if[ sum(clusterAssignment(t2,:)) < minFactors ]
                  minFactors = sum(clusterAssignment(t2,:));
                  maxFactors = sum(clusterAssignment(t1,:));
                end

                diffFactors = abs(lenTopic1 - lenTopic2);



                sumStationaryProbabilities = stationaryProbabilities(topic1) + stationaryProbabilities(topic2);

                meanFactors = sum(clusterAssignment(t1,:)) * stationaryProbabilities(topic1)/sumStationaryProbabilities +  sum(clusterAssignment(t2,:)) * stationaryProbabilities(topic2)/sumStationaryProbabilities;

		%auxilaryMatrix = resultingCluster' * resultingCluster;
		%auxilaryMatrix = auxilaryMatrix - diag( resultingCluster );
		%resultingVector = diag(transitionMatrix * auxilaryMatrix');

		%maxCohesion = 1.0/numFactors;  %max internal cohesion

		
                %meanCohesion = sum(resultingVector)/( numFactors*(numFactors-1) );
		%deltaCohesion = (meanCohesion - maxCohesion)/maxCohesion;
                
                

		%transitionProbability = (matrix(i,j) + matrix(j,i))/2;
		%deltaUnicity = (transitionProbability - minProbability)/minProbability;
                
                %unicity = sum(irreducibleMatrix(topic1,:)) + sum(irreducibleMatrix(topic2,:)) - irreducibleMatrix(topic1,topic1) - irreducibleMatrix(topic2,topic2) - irreducibleMatrix(topic1,topic2) - irreducibleMatrix(topic2,topic1);


                %sumOfLeavingProbabilities = irreducibleMatrix(topic1,:) + irreducibleMatrix(topic2,:);
                %numberOfOutlinks = size(find(sumOfLeavingProbabilities),2) - 2

                %unicity = 1 - ( unicity / count);
                
                minImportance = stationaryProbabilities(topic1);

                if[ minImportance > stationaryProbabilities(topic2) ]
                  minImportance = stationaryProbabilities(topic2);
                end

                sumImportances = ( stationaryProbabilities(topic1) + stationaryProbabilities(topic2) );
                statProb1 = stationaryProbabilities(topic1);
                statProb2 = stationaryProbabilities(topic2);
                meanImportances = sumImportances/2;
                diffImportances = abs( stationaryProbabilities(topic1) - stationaryProbabilities(topic2) );

                %beta = (sumImportances/stationaryProbabilities(topic1) + sumImportances/stationaryProbabilities(topic2)) / 2;
                %beta = (diffImportances/minImportance) ;
                
                alpha = ( ( min(lenTopic1,lenTopic2) + lenTopic1+lenTopic2 ) / ( min(lenTopic1,lenTopic2)*(lenTopic1+lenTopic2) ) );
                
                %beta = diffImportances + alpha
                beta = 1 + log(1 + 1 /numFactors);
                beta = 1 + log(numFactors/(lenTopic1*lenTopic2)) / log(2.0) ;
                %beta = (100*sumImportances/(((100*statProb1)*(100*statProb2)));
                


                %beta = beta * beta;
                
                %beta =  log( ( ( min(statProb1,statProb2) + statProb1+statProb2 ) / ( min(statProb1,statProb2)*(statProb1+statProb2) ) ) );
                %beta =  1
                
                %cohesion = sqrt( irreducibleMatrix(topic1,topic2) * irreducibleMatrix(topic2,topic1) ) * beta ;

                %cohesion = sqrt( irreducibleMatrix(topic1,topic2) * irreducibleMatrix(topic2,topic1) ) * beta ;
                
                %cohesion = sqrt( irreducibleMatrix(topic1,topic2) * irreducibleMatrix(topic2,topic1) );
                
                %cohesion = 0.0; %baseline mode
                
                cohesion = sqrt( irreducibleMatrix(topic1,topic2) * irreducibleMatrix(topic2,topic1) ) * (1 + 1/numFactors ) ;
                
                %cohesion = sqrt( irreducibleMatrix(topic1,topic2) * irreducibleMatrix(topic2,topic1) );
                %cohesion = sqrt( irreducibleMatrix(topic1,topic2) * irreducibleMatrix(topic2,topic1) ) * (1 + 1/(1.0+ diffFactors) ) ;
                %cohesion = sqrt( irreducibleMatrix(topic1,topic2) * irreducibleMatrix(topic2,topic1) ) * (1 + (diffFactors+1)/(maxFactors) );
                
                %cohesion = sqrt( irreducibleMatrix(topic1,topic2) * irreducibleMatrix(topic2,topic1) ) * beta;
                
                %cohesion = sqrt( irreducibleMatrix(topic1,topic2) * irreducibleMatrix(topic2,topic1) ) * ( 1 + 1/log(1 + minFactors) ) ;
		deltaCohesion = (cohesion - minProbability)/minProbability;
		%deltaCohesion = (cohesion - minProbability)/minProbability * log(1 + 1/minFactors);
		
                %deltaCohesion = (cohesion - minProbability)/minProbability;

               % probabilitiesJoinedTopics = (irreducibleMatrix( topic1,:) + irreducibleMatrix(topic2,:) ) / 2;
               % %probabilitiesJoinedTopics(topic1) = ;
               % %probabilitiesJoinedTopics(topic2) = 0;

               % %leavingProb1 = sum(irreducibleMatrix(topic1,:)) - irreducibleMatrix(topic1,topic1);
               % %outLinks1 = size(find(irreducibleMatrix(topic1,:)),2) - 1;
               % %minProb1 = leavingProb1 / outLinks1;
               % 
               % %leavingProb2 = sum(irreducibleMatrix(topic2,:)) - irreducibleMatrix(topic2,topic2);
               % %outLinks2 = size(find(irreducibleMatrix(topic2,:)),2) - 1;
               % %minProb2 = leavingProb2 / outLinks2;

               % %meanMinProb = (minProb1+minProb2)/2;
               % 
	       % %deltaCohesion = (cohesion - meanMinProb)/meanMinProb;

               % for k= 1:(numTopics),
               %   probabilitiesJoinedTopics(k) = irreducibleMatrix( topic1, k) * stationaryProbabilities(topic1)/(stationaryProbabilities(topic1) + stationaryProbabilities(topic2)) + irreducibleMatrix( topic2, k) * stationaryProbabilities(topic2)/(stationaryProbabilities(topic1) + stationaryProbabilities(topic2));
               % end

               % probabilitiesJoinedTopics(topic1) = 0;
               % probabilitiesJoinedTopics(topic2) = 0;

               % dotProduct = probabilitiesJoinedTopics .* ( irreducibleMatrix(:,topic1)' + irreducibleMatrix(:,topic2)' );
               % squaredProducts = sqrt(dotProduct);
               % sumMutualTransition = sum(squaredProducts);
               % 
               % numberOfOutlinks = size(find(probabilitiesJoinedTopics),2);
               % spreading = numTopics - 1 - numberOfOutlinks;

               % unicity = sumMutualTransition/spreading;
               % %unicity = 1/spreading;
               % 

	       % deltaUnicity = (unicity - ( 1 / (numTopics -1 - meanNumberOfLinks) ) ) / ( 1 / (numTopics -1 - meanNumberOfLinks) );
	       % %deltaUnicity = (minProbability - unicity)/minProbability;
	       % %deltaUnicity = (minProbability - unicity);
                
                fprintf(outputFileCohesion,'%g\n', cohesion);
               % fprintf(outputFileUnicity,'%g\n', unicity);

                fprintf(outputFileDeltaCohesion,'%g\n', deltaCohesion);
               % fprintf(outputFileDeltaUnicity,'%g\n',deltaUnicity);

                alpha = 1;
	        temporaryMatrix(i,j) = alpha*deltaCohesion;
		%temporaryMatrix(i,j) = cohesion * log(1+unicity) -  (minProbability * (1/numTopics));
		%temporaryMatrix(i,j) = deltaCohesion - minProbability;
		%temporaryMatrix(i,j) = cohesion;
		%temporaryMatrix(i,j) = alpha*cohesion + (1.0 - alpha)*deltaUnicity;
		%fprintf('%g  %g  %g  %g  %g  %g  %g  %g  %g\n', i, j, matrix(i,j), matrix(j,i), transitionProbability, deltaCohesion, deltaUnicity, alpha, temporaryMatrix(i,j));
	  end

      end

      fclose(outputFileCohesion)
      fclose(outputFileDeltaCohesion)
      
      fclose(outputFileDeltaUnicity)
      fclose(outputFileUnicity)
      probabilities = reshape(temporaryMatrix',matrixSize,1);
      [sortedProbabilities, indices] = sort(probabilities, 'descend');

      prob = sortedProbabilities(1);

      index = 1;
      for i= 1:matrixSize,
		if [ sortedProbabilities(i) == 0 ]
			break;
		end

		selectedRow = floor(indices(i)/numTopics) + 1;
		selectedColumn = mod(indices(i),numTopics);
		if [ selectedColumn == 0 ]
			selectedRow = selectedRow - 1;
			selectedColumn = numTopics;
		end

		if [ (dirtyTopics(selectedColumn) ~= 1) && (dirtyTopics(selectedRow) ~= 1 ) ]
			selectedRows(index) = topicIndexes(selectedRow);
			selectedColumns(index) = topicIndexes(selectedColumn);
			maxProbabilities(index) = sortedProbabilities(i);
			index = index + 1;

			dirtyTopics(selectedColumn) = 1;
			dirtyTopics(selectedRow) = 1;	
		end

      end

