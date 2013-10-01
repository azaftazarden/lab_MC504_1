Grupo: 
	Marcelo Abiarraj ra: 122128
	Rafael Gouvêa	 ra: 106905

Problema:	Papai Noel
	Papai está dormindo, os elfos estão trabalhando nos presentes e as Renas estão viajando.
Quando três elfos precisam de ajuda, eles acordam o papai noel, que ajuda os elfos, e depois volta a dormir. Enquanto isso, as renas vão chegando no polo norte.Quando 9 renas chegam, elas acordam o Papai Noel e partem, daí o programa acaba.

Solução:
	As renas são um vetor de 9 threads, que tem sua área de código protegida por um mutex.
Os elfos são uma thread só, que executa em loop infinito.
O Papai noel também é um thread só, ela executa um loop vazio (busy wait) controlado pela variavel "acordado" que e mudada pelos elfos ou pelas renas nas condições certas.


