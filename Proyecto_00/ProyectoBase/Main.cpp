#include <SFML\Network.hpp>
#include <iostream>

#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

#define MAX_MENSAJES 30
void thread_receive() {

}

int main()
{
	std::cout << "REDES - Taller 1:" << std::endl;
	std::cout << "******************" << std::endl;
	std::cout << "Elige un modo de abrir el chat:" << std::endl;
	std::cout << "1. Blocking + Threading" << std::endl;
	std::cout << "2. NonBlocking" << std::endl;
	std::cout << "3. Blocking + SocketSelector" << std::endl;

	int mode;
	std::cin >> mode;
	switch (mode)
	{
	case 1:
		std::cout << "Has elegido el modo 1 (Blocking + Threading)" << std::endl;
		break;

	case 2:
		std::cout << "Has elegido el modo 2 (NonBlocking)" << std::endl;
		break;

	case 3:
		std::cout << "Has elegido el modo 3 (Blocking + SocketSelector)" << std::endl;
		break;
	default:
		break;
	}



	std::cout << "¿Seras servidor (s) o cliente (c)? ... ";
	char c;
	std::cin >> c;
	sf::TcpSocket socket;
	std::string textoAEnviar="";
	if (c == 's')
	{
		sf::TcpListener listener;
		listener.listen(50000);
		listener.accept(socket);
		textoAEnviar = "Mensaje desde servidor\n";
	}
	else if (c == 'c')
	{
		socket.connect("localhost", 50000, sf::milliseconds(15.f));
		textoAEnviar = "Mensaje desde cliente\n";

	}
	else
	{
		exit(0);
	}

	std::string texto = "Conexion con ... " + (socket.getRemoteAddress()).toString() + ":" + std::to_string(socket.getRemotePort()) + "\n";
	std::cout << texto;

	socket.send(textoAEnviar.c_str(), texto.length());

	char buffer[100];
	size_t bytesReceived;
	socket.receive(buffer, 100, bytesReceived);

	buffer[bytesReceived] = '\0';
	std::cout << "Mensaje recibido: " << buffer << std::endl;














	//CHAT
	std::vector<std::string> aMensajes;

	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Chat");

	sf::Font font;
	if (!font.loadFromFile("nasalization-rg.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}

	sf::String mensaje = " >";

	sf::Text chattingText(mensaje, font, 14);
	chattingText.setFillColor(sf::Color(0, 160, 0));
	chattingText.setStyle(sf::Text::Bold);


	sf::Text text(mensaje, font, 14);
	text.setFillColor(sf::Color(0, 160, 0));
	text.setStyle(sf::Text::Bold);
	text.setPosition(0, 560);

	sf::RectangleShape separator(sf::Vector2f(800, 5));
	separator.setFillColor(sf::Color(200, 200, 200, 255));
	separator.setPosition(0, 550);

	while (window.isOpen())
	{
		sf::Event evento;
		while (window.pollEvent(evento))
		{
			switch (evento.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evento.key.code == sf::Keyboard::Escape)
					window.close();
				else if (evento.key.code == sf::Keyboard::Return)
				{
					aMensajes.push_back(mensaje);
					if (aMensajes.size() > 25)
					{
						aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
					}
					mensaje = ">";
				}
				break;
			case sf::Event::TextEntered:
				if (evento.text.unicode >= 32 && evento.text.unicode <= 126)
					mensaje += (char)evento.text.unicode;
				else if (evento.text.unicode == 8 && mensaje.getSize() > 0)
					mensaje.erase(mensaje.getSize() - 1, mensaje.getSize());
				break;
			}
		}
		window.draw(separator);
		for (size_t i = 0; i < aMensajes.size(); i++)
		{
			std::string chatting = aMensajes[i];
			chattingText.setPosition(sf::Vector2f(0, 20 * i));
			chattingText.setString(chatting);
			window.draw(chattingText);
		}
		std::string mensaje_ = mensaje + "_";
		text.setString(mensaje_);
		window.draw(text);


		window.display();
		window.clear();
	}





	
	//system("pause");
	
	return 0;

}