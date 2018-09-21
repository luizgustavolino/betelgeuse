//Dimensoes da tela
const int larguraTela = 550; //factor 2.5 from (220x176)
const int alturaTela = 440;  //factor 2.5 from (220x176)
float factor = 2.5;

//variavel janela principal
ALLEGRO_DISPLAY *janela = NULL;
//variavel imagem
ALLEGRO_BITMAP *imagem,*botaoA,*botaoOpcoes = NULL;
//variavel fila de eventos
ALLEGRO_EVENT_QUEUE *filaEventos = NULL;

//verificar se o jogo foi fechado
bool sairJogo = false;

//inicializar funcoes
bool inicializarComandos();
bool configurarVariaveis();
void desenharImagens();
void desalocarVariaveis();
void iniciarJogo();


ALLEGRO_BITMAP *carregarBitmapResized(const char *filename){
  ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;
  float w, h;

  loaded_bmp = al_load_bitmap(filename);
  w = factor * al_get_bitmap_width(loaded_bmp);
  h = factor * al_get_bitmap_height(loaded_bmp);

  // 1. create a temporary bitmap of size we want
  resized_bmp = al_create_bitmap(w, h);
  if (!resized_bmp) {
     return NULL;
  }

  // 2. load the bitmap at the original size
  if (!loaded_bmp)
  {
     al_destroy_bitmap(resized_bmp);
     return NULL;
  }

  // 3. set the target bitmap to the resized bmp
  prev_target = al_get_target_bitmap();
  al_set_target_bitmap(resized_bmp);

  // 4. copy the loaded bitmap to the resized bmp
  al_draw_scaled_bitmap(loaded_bmp,
     0, 0,                                // source origin
     al_get_bitmap_width(loaded_bmp),     // source width
     al_get_bitmap_height(loaded_bmp),    // source height
     0, 0,                                // target origin
     w, h,                                // target dimensions
     0                                    // flags
  );

  // 5. restore the previous target and clean up
  al_set_target_bitmap(prev_target);
  al_destroy_bitmap(loaded_bmp);

  return resized_bmp;
}

void desalocarVariaveis(){
    al_destroy_display(janela);
    al_destroy_bitmap(imagem);
    al_destroy_event_queue(filaEventos);
}

bool inicializarComandos(){
    al_init();
    if(!al_init()){
        fprintf(stderr, "Falha ao inicializar a biblioteca allegro.\n");
        return false;
    }

    al_init_image_addon();
    if(!al_init_image_addon()){
        fprintf(stderr, "Falha ao inicializar a biblioteca de imagem.\n");
        return false;
    }

    if(!al_install_keyboard()){
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    return true; //Tudo foi inicializado corretamente
}

bool configurarVariaveis(){

    janela = al_create_display(larguraTela, alturaTela);
    if(!janela){
        fprintf(stderr, "Falha ao criar a janela.\n");
        desalocarVariaveis();
        return false;
    }

    filaEventos = al_create_event_queue();
    if(!filaEventos){
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        desalocarVariaveis();
        return false;
    }

    return true; //Tudo foi configurado corretamente
}

bool carregarImagens(){

    imagem = carregarBitmapResized("splash.png");
    botaoA = carregarBitmapResized("button-A.png");
    botaoOpcoes = carregarBitmapResized("button-opcoes.png");

    if(!imagem){
        fprintf(stderr, "Falha ao atribuir imagem tela inicial.\n");
        desalocarVariaveis();
        return false;
    }
}

void desenharImagens(){
    al_draw_bitmap(imagem, 0, 0, 0);
    al_flip_display();
}

void buttonFlicker(){


}

void iniciarJogo(){

    int contagemTelas = 0;

    al_register_event_source(filaEventos, al_get_keyboard_event_source());
    al_register_event_source(filaEventos, al_get_display_event_source(janela));

    //Carrega as imagens do Jogo.
    carregarImagens();
    //Desenha o splash
    desenharImagens();
    //Espera um momento e desenha o botão A para continuar para a Tela Inicial
    al_rest(2.0);
    al_draw_bitmap(botaoA,larguraTela-55,alturaTela-50,0);
    al_flip_display();

    while(!sairJogo){
        while(!al_is_event_queue_empty(filaEventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaEventos, &evento);

            // O elemento 'contagemTelas' memoriza as telas já desenhadas.
            // Desenha a Tela Inicial do jogo.
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN && contagemTelas == 0){
                switch(evento.keyboard.keycode){
                case ALLEGRO_KEY_E:
                    printf("Tecla 'E' foi pressionada\n");
                    imagem = carregarBitmapResized("tela-inicial.png");
                    desenharImagens();
                    // Descansa 2 segundos antes de desenhar o botão opções.
                    al_rest(2.0);
                    al_draw_bitmap(botaoOpcoes,larguraTela-185,alturaTela-60,0);
                    al_flip_display();
                    // Soma mais um para que a tela inicial não seja desenhada novamente.
                    contagemTelas++;

                    break;
                }
            }

            else if(evento.type == ALLEGRO_EVENT_KEY_DOWN && contagemTelas == 1){
                switch(evento.keyboard.keycode){
                case ALLEGRO_KEY_E:
                    printf("Tecla 'E' foi pressionada\n");
                    desenharImagens();
                    imagem = carregarBitmapResized("shared.menus.png");
                    desenharImagens();
                    al_rest(2.0);
                    al_draw_bitmap(botaoA,larguraTela-55,alturaTela-50,0);
                    al_flip_display();
                    contagemTelas++;

                    break;
                }
            }

            else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                printf("\nO jogo foi encerrado\n");
                sairJogo = true;
            }
        }
    }

    desalocarVariaveis();
}
