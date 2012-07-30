//Mesh.h
#include "Advanced2D.h"
#include "Entity.h"

namespace Advanced2D
{
	class Mesh : public Entity
	{
		public:
			Mesh();
			~Mesh();
			int GetFaceCount()const;
			int GetVertexCount()const;
			bool Load(char* filename);
			void CreateSphere(float radius,int slices,int stacks);
			void CreateCube(float width,float height,float depth);
			void Draw();
			void Transform();
			void SetPosition(const D3DXVECTOR3& pos);
			void SetPosition(float x,float y,float z);
			void SetScale(const D3DXVECTOR3& scale);
			void SetScale(float x,float y,float z);
			void SetVelocity(const D3DXVECTOR3& vel);
			void SetVelocity(float x,float y,float z);
			void Rotate(D3DXVECTOR3 rot);
			void Rotate(float x,float y,float z);
			void Update();
			void LimitBoundary(float left,float right,float top,float bottom,float front,float back);
		private:
			LPD3DXMATERIAL d3dxMaterials;
			LPD3DXBUFFER matBuffer;
			D3DMATERIAL9* materials;
			LPDIRECT3DTEXTURE9* textures;
			LPD3DXMESH mesh;
			DWORD materialCount;
			D3DXVECTOR3 position;
			D3DXVECTOR3 velocity;
			D3DXVECTOR3 rotation;
			D3DXVECTOR3 scale;
			D3DXMATRIX  matRotate;
			D3DXMATRIX  matScale;
			D3DXMATRIX  matTranslation;
			D3DXMATRIX  matWorld;
	};
};
