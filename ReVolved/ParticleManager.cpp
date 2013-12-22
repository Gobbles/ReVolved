#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
	particles = std::vector<std::unique_ptr<Particle> >();
}

ParticleManager::~ParticleManager()
{}

void ParticleManager::AddParticle(Particle& newParticle)
{
	AddParticle(newParticle, false);
}

void ParticleManager::AddParticle(Particle& newParticle, bool background)
{
	//newParticle.Background = background;
	//particles.push_back(newParticle);
}
void ParticleManager::UpdateParticles(float frameTime)
{
	for (int i = particles.size() - 1; i > 0; --i)
    {
		particles[i]->Update(frameTime);
		if (!particles[i]->Exists)
        {
			particles.erase(particles.begin() + i);
        }
    }
}
void ParticleManager::DrawParticle(sf::RenderWindow& window, sf::Sprite& sprite, bool background)
{
    //particleTexture.clear();
	for(int i = 0; i < particles.size(); i++)
	{
		if (!particles[i]->Additive && particles[i]->Background == background)
            particles[i]->Draw(window, sprite);
	}
	for(int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->Additive && particles[i]->Background == background)
            particles[i]->Draw(window, sprite);
	}
}
void ParticleManager::MakeShot(sf::Vector2f loc, sf::Vector2f traj, int face, int owner)
{
	switch(face)
	{
	case 0:
	//	/*AddParticle(std::make_shared<Shot>(loc, sf::Vector2f(-traj.x, traj.y)
	//		+ Commands::GetRandomVector2(-90.f, 9.0f, -90.f, 90.f), owner));

	//	MakeShotFlash(loc, sf::Vector2f(-traj.x, traj.y));*/
		break;
	case 1:
	//	//AddParticle(std::make_shared<Shot>(loc, traj +
	//	//	Commands::GetRandomVector2(-90.f, 90.f, -90.f, 90.f), owner));

	//	MakeShotFlash(loc, traj);
		break;
	}
}
void ParticleManager::MakeShotFlash(sf::Vector2f loc, sf::Vector2f traj)
{
	/*for (int i = 0; i < 16; i++)
    {
        AddParticle(std::make_shared<shotFlash>(loc + (traj * (float)i) * 0.001f +
           GetRandomVector2(-5.f, 5.f, -5.f, 5.f),
            traj / 5f, (20f - (float)i) * 0.06f));
    }
    for (int i = 0; i < 4; i++)
        AddParticle(new Smoke(loc, GetRandomVector2(-30f, 30f, -100f, 0f),
            0f, 0f, 0f, 0.25f, GetRandomFloat(0.25f, 1.0f),
            Rand.GetRandomInt(0, 4)));*/
}
void ParticleManager::MakeShotDust(sf::Vector2f loc, sf::Vector2f traj)
{
	//for (int i = 0; i < 8; i++)
    //{
        //AddParticle(new Smoke(loc, Rand.GetRandomVector2(0f, 0f, 0f, 0f)
        //    - traj * Rand.GetRandomFloat(0.001f, 0.1f), 1f, 1f, 1f, 0.25f,
        //    Commands::GetRandomFloat(0.05f, 0.25f), Rand.GetRandomInt(0, 4)));
        //AddParticle(new Smoke(loc, Rand.GetRandomVector2(-50f, 50f, -25f, 10f),
        //    0.5f, 0.5f, 0.5f, 0.15f, Rand.GetRandomFloat(0.1f, 0.3f),
        //    Commands::GetRandomInt(0, 4)));
    //}
}
void ParticleManager::MakeBulletBlood(sf::Vector2f loc, sf::Vector2f traj)
{
	/*for (int t = 0; t < 32; t++)
	{
        AddParticle(std::make_shared<Blood>(
        loc,
        traj *
        -1.f * GetRandomFloat(0.01f, 0.1f) +
        GetRandomVector2(-50.f, 50.f, -50.f, 50.f),
        1.f, 0.f, 0.f, 1.f,
        GetRandomFloat(0.1f, 0.3f),
        GetRandomInt(0, 4)));
	}*/
}
void ParticleManager::MakeBloodSplash(sf::Vector2f loc, sf::Vector2f traj)
{
}

void ParticleManager::MakeFire(sf::Vector2f loc, sf::Vector2f traj, int icon)
{
	std::unique_ptr<Fire> fire = std::unique_ptr<Fire>(new Fire(loc, traj, GetRandomFloat(0.25f, 0.75f), icon));
	fire->Background = true;
	particles.push_back(std::move(fire));
}