
class NeuralNetwork{
private:
    const static int layerAmmount = 3;
    const int layers[layerAmmount] = {9, 18, 9};
    const int population = 100000;
    const int cycles = 1000;
    struct net{
    double **neurons = new double*[layerAmmount];
    double ***weights = new double**[layerAmmount];
};
public:
    void initNet(net *net);
    void mutate(net *net);
    void deleteNet(net *net);

void initNet(net *net){

    // Make and init neurons
    for(int i = 0; i < layerAmmount; i++){
         (*net).neurons[i] = new double[layers[i]];
        for(int j = 0; j < layers[i]; j++){
           (*net).neurons[i][j] = 0;
        }
    }  

    // Make and init weights
    for(int i = 1; i < layerAmmount; i++){

        // First layer of pointers
        (*net).weights[i] = new double*[layers[i]];
        for(int j = 0; j < layers[i]; j++){

            // Actual values
            (*net).weights[i][j] = new double[layers[i - 1]];
            for(int k = 0; k < layers[i - 1]; k++){

                // Init to random
                (*net).weights[i][j][k] = (double) rand()/RAND_MAX;
            }
        }
    }
}

void mutate(net *net){
    double weight;
    // Loop over all weights
    for(int i = 1; i < layerAmmount; i++){
        for(int j = 0; j < layers[i]; j++){
            for(int k = 0; k < layers[i - 1]; k++){

                // Mutate
                weight = (*net).weights[i][j][k];

                // Change the number based on chance
                int randNumber = rand() % 100;

                if(randNumber <= 2){
                    // Flip sign
                    weight *= -1;
                }else if(randNumber <= 4){
                    // Change it from a random number between 1 and -1
                    weight = (double) rand()/RAND_MAX;
                }else if(randNumber <= 6){
                    // Increase by 0% to 100%
                    weight *= (double) rand()/RAND_MAX + 1;
                }else if(randNumber <= 8){
                    // Decrease by 0% to 100%
                    weight *= (double) rand()/RAND_MAX ;
                }
                // Apply changes
                (*net).weights[i][j][k] = weight;
            }
        }
    }
}

void deleteNet(net *net){
    // Delete weights
    for(int i = 1; i < layerAmmount; i++){
        for(int j = 0; j < layers[i]; j++){
               delete (*net).weights[i][j];
         }
        delete (*net).weights[i];
     }
    delete[] (*net).weights;

    // Neurons
    for(int i = 1; i < layerAmmount; i++){
        delete (*net).neurons[i];
    }
    delete[] (*net).neurons;
}
};