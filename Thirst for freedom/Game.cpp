#include "Game.h"

Game::Game(void)
{
	Initialize();
	arnold = new Arnold(vec2f(0.f,0.f), vec2f(4.f,5.f), "Arnold");
	
	room = new Room("001", arnold);
	clock.restart();
	
	window->setVerticalSyncEnabled(true);
	window->setActive(false);

	thread = new sf::Thread(&Game :: Thread, this);

	thread->launch();

	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			arnold->Control();
			if(event.type == sf::Event::Closed) window->close();
		}
		sf::sleep(sf::milliseconds(100));
	}
}

void Game :: Thread()
{
	while (window->isOpen())
	{
		GetTimeAndMousePositionion();
		if(game_State == GAME_STATE::GAME)
		{
			arnold->Update();
		
			for(std::list<Unit*>::iterator it1 = Unit :: unit_List.begin(); it1 != Unit :: unit_List.end(); it1++)
			{
				Unit* u1 = *it1;
				for(std::list<Unit*>::iterator it2 = it1; it2 != Unit :: unit_List.end(); it2++)
				{
					Unit* u2 = *it2;
					if(u1 != u2 && u1->InterRect(u2->GetRect()))
					{
						if(u1->GetIsLife() && u2->GetIsLife()) 
						{
							u1->MoveToAngle(-u1->GetMoveSpeed(), u1->GetAngPos(u2->GetPos()));
							u2->MoveToAngle(-u2->GetMoveSpeed(), u2->GetAngPos(u1->GetPos()));
						}
					}
				}
			}
		}

		for(std::list<Unit*>::iterator it = Unit :: unit_List.begin(); it != Unit :: unit_List.end(); it++)
		{
			Unit* u = *it;
			for(auto w: Wall :: wall_List)
			{
				if(u->GetState() != 6 && u->GetIsLife())
				{
					if(w->GetIsQuad())
						while(u->InterRect(w->GetRect()))
							u->MoveToAngle(-u->GetMoveSpeed(), u->GetAngPos(w->GetPos()));
					else
						while(u->GetDistPos(w->GetPos()) <= u->GetSize().x/2.f + w->GetSize().x/2.f)
							u->MoveToAngle(-u->GetMoveSpeed(), u->GetAngPos(w->GetPos()));
				}

				for(std::list<Missle*>::iterator it = Missle :: missle_List.begin(); it != Missle :: missle_List.end();)
				{
					Missle* m = *it;
					if(m->GetDistPos(w->GetPos()) <= w->GetSize().x/2.f)
					{
						it = Missle::missle_List.erase(it); 
						delete m;
					}
					else it++;
				}
			}
		}

		window->clear();

		for(auto t: Terrain :: terrain_List) t->Draw();
		for(auto a: Sprite :: ambience_List) a->Draw();
		for(auto w: Wall :: wall_List) w->Draw();

		for(auto u: Unit :: unit_List) 
			if(u!=arnold) u->Draw();
		arnold->Draw();

		for(auto m: Missle :: missle_List) m->Draw();
		for(auto u: Sprite :: ui_List) u->Draw();

		window->display();
	}
}

int main()
{
	Game play;
	play.thread->wait();

	return 0;
}

// class ParticleSystem : public sf::Drawable, public sf::Transformable 
// { 
// 	public: 
// 	
// 	ParticleSystem(unsigned int count, sf::Vector2f p) : 
// 	m_particles(count), 
// 	m_vertices(sf::Points, count), 
// 	m_lifetime(sf::seconds(3)), 
// 	m_emitter(p.x, p.y) // ”кажите позицию в этот метод
// { 
// 
// } 
// 	
// void setEmitter(sf::Vector2f position) 
// { 
// 	m_emitter = position; 
// } 
// 	
// void update(sf::Time elapsed) 
// { 
// 	for (std::size_t i = 0; i < m_particles.size(); ++i) 
// 	{ 
// 		// update the particle lifetime 
// 		Particle& p = m_particles[i]; 
// 		p.lifetime -= elapsed; 
// 
// 		// if the particle is dead, respawn it 
// 		if (p.lifetime <= sf::Time::Zero) 
// 		resetParticle(i); 
// 		
// 		// update the position of the corresponding vertex 
// 		m_vertices[i].position += p.velocity * elapsed.asSeconds();
// 		
// 		// update the alpha (transparency) of the particle according to its lifetime 
// 		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds(); 
// 		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255); 
// 		m_vertices[i].color.r = sf::Uint8(255);
// 		m_vertices[i].color.g = sf::Uint8(255);
// 		m_vertices[i].color.b = sf::Uint8(0);
// 	} 
// } 
// 
// private: 
// 
// virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
// { 
// // apply the transform 
// states.transform *= getTransform(); 
// 
// // our particles don't use a texture 
// states.texture = NULL; 
// 
// // draw the vertex array 
// target.draw(m_vertices, states); 
// } 
// 
// private: 
// 
// struct Particle 
// { 
// sf::Vector2f velocity; 
// sf::Time lifetime; 
// }; 
// 
// void resetParticle(std::size_t index) 
// { 
// // give a random velocity and lifetime to the particle 
// float angle = (std::rand() % 360) * 3.14f / 180.f; 
// float speed = (std::rand() % 50) + 50.f; 
// m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed); 
// m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000); 
// 
// // reset the position of the corresponding vertex 
// m_vertices[index].position = m_emitter; 
// } 
// 
// std::vector<Particle> m_particles; 
// sf::VertexArray m_vertices; 
// sf::Time m_lifetime; 
// sf::Vector2f m_emitter; 
// }; 
// 
// int main() 
// { 
// // create the window 
// sf::RenderWindow window(sf::VideoMode(512, 256), "Particles"); 
// 
// // create the particle system 
// ParticleSystem particles_1(1000, sf::Vector2f(100, 100));
// ParticleSystem particles_2(1000, sf::Vector2f(300, 100));
// 
// // create a clock to track the elapsed time 
// sf::Clock clock; 
// 
// // run the main loop 
// while (window.isOpen()) 
// { 
// // handle events 
// sf::Event event; 
// while (window.pollEvent(event)) 
// { 
// if(event.type == sf::Event::Closed) 
// window.close(); 
// } 
// 
// // make the particle system emitter follow the mouse 
// 
// // update it 
// sf::Time elapsed = clock.restart(); 
// particles_1.update(elapsed);
// particles_2.update(elapsed);
// 
// // draw it 
// window.clear( ); 
// window.draw(particles_1);
// window.draw(particles_2);
// window.display(); 
// } 
// 
// return 0; 
// }