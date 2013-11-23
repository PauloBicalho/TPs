#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

class Automato{
  public:



  private:
    enum Estado {
      ESPERANDO_ID,
      ESPERANDO_CONFIRMACAO_INTEVALOS,
      ESPERANDO_RESPOSTA;
    };

    enum Acao {
      ENVIAR_ITERVALOS,
      REENVIAR_INTERVALOS,
      CONFIRMAR_RESPOSTA,
    };


};



#endif // AUTOMATO_HPP
