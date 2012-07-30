//Mesh.cpp
#include "Mesh.h"

namespace Advanced2D
{
	Mesh::Mesh() : Entity(RENDER3D)
	{
		mesh = 0;
		materials = 0;
		d3dxMaterials = 0;
		matBuffer = 0;
		materialCount = 0;
		textures = 0;
		position = D3DXVECTOR3(0.0f,0.0f,0.0f);
		rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
		velocity = D3DXVECTOR3(0.0f,0.0f,0.0f);
		scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	}

	Mesh::~Mesh()
	{
		if(materials != NULL) delete[] materials;

		if(textures != NULL)
		{
			for(DWORD i = 0; i < materialCount; i++)
			{
				if(textures[i] != NULL)
					textures[i]->Release();
			}
			delete[] textures;
		}

		if(mesh != NULL) mesh->Release();
	}

	int Mesh::GetFaceCount()const
	{
		return mesh->GetNumFaces();
	}

	int Mesh::GetVertexCount()const
	{
		return mesh->GetNumVertices();
	}

	bool Mesh::Load(char* filename)
	{
		HRESULT result;

		result = D3DXLoadMeshFromX(
			filename,
			D3DXMESH_SYSTEMMEM,
			g_engine->GetDevice(),
			NULL,
			&matBuffer,
			NULL,
			&materialCount,
			&mesh);

		if(result != D3D_OK)
		{
			return false;
		}

		d3dxMaterials = (LPD3DXMATERIAL)matBuffer->GetBufferPointer();
		materials = new D3DMATERIAL9[materialCount];
		textures = new LPDIRECT3DTEXTURE9[materialCount];

		for(DWORD mat = 0; mat < materialCount; mat++)
		{
			materials[mat] = d3dxMaterials[mat].MatD3D;
			materials[mat].Ambient = materials[mat].Diffuse;
			materials[mat].Power = 0.5f;
			//materials[mat].Specular = materials[mat].Diffuse;

			textures[mat] = NULL;
			if(d3dxMaterials[mat].pTextureFilename != NULL &&
				lstrlen(d3dxMaterials[mat].pTextureFilename) > 0)
			{
				result = D3DXCreateTextureFromFile(g_engine->GetDevice(),
					d3dxMaterials[mat].pTextureFilename,&textures[mat]);
			

				if(result != D3D_OK)
				{
					return false;
				}
			}
		}
		matBuffer->Release();

		return true;
	}

	void Mesh::CreateSphere(float radius,int slices, int stacks)
	{
		D3DXCreateSphere(g_engine->GetDevice(),radius,slices,stacks,&mesh,NULL);
	}

	void Mesh::CreateCube(float height,float width,float depth)
	{
		D3DXCreateBox(g_engine->GetDevice(),width,height,depth,&mesh,NULL);
	}

	void Mesh::Draw()
	{
		if(materialCount == 0)
		{
			mesh->DrawSubset(0);
		}
		else
		{
			for(DWORD set = 0; set < materialCount; set++)
			{
				g_engine->GetDevice()->SetMaterial(&materials[set]);

				if(textures[set])
				{
					if(textures[set]->GetType() == D3DRTYPE_TEXTURE)
					{
						D3DSURFACE_DESC desc;
						textures[set]->GetLevelDesc(0,&desc);
						if(desc.Width > 0)
						{
							g_engine->GetDevice()->SetTexture(0,textures[set]);
						}
					}
				}
				mesh->DrawSubset(set);
			}
		}

	}

	void Mesh::Transform()
	{
		float x = D3DXToRadian(rotation.x);
		float y = D3DXToRadian(rotation.y);
		float z = D3DXToRadian(rotation.z);
		D3DXMatrixRotationYawPitchRoll(&matRotate,x,y,z);

		D3DXMatrixScaling(&matScale,scale.x,scale.y,scale.z);

		D3DXMatrixTranslation(&matTranslation,position.x,position.y,position.z);

		matWorld = matRotate * matScale * matTranslation;
		g_engine->GetDevice()->SetTransform(D3DTS_WORLD,&matWorld);
	}

	void Mesh::SetPosition(const D3DXVECTOR3& pos)
	{
		SetPosition(pos.x,pos.y,pos.z);
	}

	void Mesh::SetPosition(float x,float y,float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void Mesh::SetScale(const D3DXVECTOR3& scale)
	{
		SetScale(scale.x,scale.y,scale.z);
	}

	void Mesh::SetScale(float x,float y,float z)
	{
		scale.x = x;
		scale.y = y;
		scale.z = z;
	}

	void Mesh::SetVelocity(const D3DXVECTOR3& vel)
	{
		SetVelocity(vel.x,vel.y,vel.z);
	}

	void Mesh::SetVelocity(float x,float y,float z)
	{
		velocity.x = x;
		velocity.y = y;
		velocity.z = z;
	}

	void Mesh::Rotate(D3DXVECTOR3 rot)
	{
		Rotate(rot.x,rot.y,rot.z);
	}

	void Mesh::Rotate(float x,float y,float z)
	{
		rotation.x += x;
		rotation.y += y;
		rotation.z += z;
	}

	void Mesh::Update()
	{
		position.x += velocity.x;
		position.y += velocity.y;
		position.z += velocity.z;
	}
	void Mesh::LimitBoundary(float left,float right,float top,float bottom,float front,float back)
	{
		if(position.x < left || position.x > right)
			velocity.x *= -1;

		if(position.y < bottom || position.y > top)
			velocity.y *= -1;

		if(position.z < front || position.z > back)
			velocity.z *= -1;
	}
};