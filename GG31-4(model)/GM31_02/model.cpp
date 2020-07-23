//===================================
//Load()�֐��F���f����ǂݍ���Œ��_����ێ�
//�@�@�@�@�@�@�}�e���A����e�N�X�`����ێ�
//Draw()�֐��F�P���ɕ`��݂̂��s��
//�@�@�@�@�@�@�s��֘A��Draw()�֐����Ăяo���O��ōs���B
//
//�L�����N�^�[�Ƃ��Ă̎d���͉������Ȃ��̂ŕʓr�L�����N�^�N���X��
//�쐬���Ă��̓�����CModel�C���X�^���X������ĉ^�p����B
//
//====================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "main.h"
//#include "renderer.h"
#include "model.h"
#include "textureGL.h"//<<<<<<<<<<�t�@�C���������킹��


void CModel::Draw()
{

	// ���_�z��ݒ�
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, sizeof( VERTEX_3D_MODEL), (float*)m_Model.VertexArray + 9 );

	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer( 2, GL_FLOAT, sizeof( VERTEX_3D_MODEL), (float*)m_Model.VertexArray + 0 );
	
	glEnableClientState( GL_NORMAL_ARRAY );
	glNormalPointer( GL_FLOAT, sizeof( VERTEX_3D_MODEL), (float*)m_Model.VertexArray + 6 );

	//��]���Ȃ��獶�E�։�������i�s��̏�Z�����ɒ��Ӂj
	static GLfloat angle = 0.0f;	//�f�o�b�O�p
	static GLfloat angle2 = 0.0f;	//�f�o�b�O�p

	GLfloat posx = sinf(angle2 * (3.14159 / 180.0f))*5.0f;	//���E�̈ړ��l
	glTranslatef(posx, 0.0f, 0.0f);		//�s��X�^�b�N�֕��s�ړ��s�����Z				1
	glRotatef(angle, 1.0f, 1.0f, 1.0f);	//���݂̃J�����g�s��� X ��]�s�񂪏�Z�����	2
	//glScalef(posx*50, posx*50, posx*50);			//�s��X�^�b�N�֊g��k���s�����Z				3
	glScalef(100, 100, 100);			//�s��X�^�b�N�֊g��k���s�����Z				3

	angle += 1.0f;//�p�x�X�V
	angle2 += 1.0f;



	
	// ���f���`��
	for( unsigned int i = 0; i < m_Model.SubsetNum; i++ )
	{
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, (float*)&m_Model.SubsetArray[i].Material.Material.Ambient );
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, (float*)&m_Model.SubsetArray[i].Material.Material.Diffuse );
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, (float*)&m_Model.SubsetArray[i].Material.Material.Specular );
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, m_Model.SubsetArray[i].Material.Material.Shininess );
		
		// �e�N�X�`���ݒ�
		glBindTexture( GL_TEXTURE_2D, m_Model.SubsetArray[i].Material.Texture );
		
		// �|���S���`��
		glDrawElements( GL_TRIANGLES, m_Model.SubsetArray[i].IndexNum, GL_UNSIGNED_INT, &m_Model.IndexArray[ m_Model.SubsetArray[i].StartIndex ] );
	}

}



void CModel::Load( const char *FileName )
{

	LoadObj( FileName, &m_Model );

	// �T�u�Z�b�g�ݒ�
	{

		for( unsigned int i = 0; i < m_Model.SubsetNum; i++ )
		{
			m_Model.SubsetArray[i].Material.Texture = LoadTexture( m_Model.SubsetArray[i].Material.TextureName );
		}
	}


}





void CModel::Unload()
{
	delete[] m_Model.VertexArray;
	delete[] m_Model.IndexArray;
	delete[] m_Model.SubsetArray;
}





//���f���Ǎ�////////////////////////////////////////////
void CModel::LoadObj( const char *FileName, MODEL *Model)
{

	char dir[MAX_PATH];
	strcpy (dir, FileName );
	PathRemoveFileSpec(dir);





	VECTOR3D_MODEL	*positionArray;
	VECTOR3D_MODEL	*normalArray;
	VECTOR2D_MODEL	*texcoordArray;

	unsigned int	positionNum = 0;
	unsigned int	normalNum = 0;
	unsigned int	texcoordNum = 0;
	unsigned int	vertexNum = 0;
	unsigned int	indexNum = 0;
	unsigned int	in = 0;
	unsigned int	subsetNum = 0;

	MODEL_MATERIAL	*materialArray = NULL;
	unsigned int	materialNum = 0;

	char str[256];
	char *s;
	char c;


	FILE *file;
	file = fopen( FileName, "rt" );
	assert(file);



	//�v�f���J�E���g
	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "v" ) == 0 )
		{
			positionNum++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			normalNum++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			texcoordNum++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			subsetNum++;
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			in = 0;

			do
			{
				fscanf( file, "%s", str );
				vertexNum++;
				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c!= '\r' );

			//�l�p�͎O�p�ɕ���
			if( in == 4 )
				in = 6;

			indexNum += in;
		}
	}


	//�������m��
	positionArray = new VECTOR3D_MODEL[ positionNum ];
	normalArray = new VECTOR3D_MODEL[ normalNum ];
	texcoordArray = new VECTOR2D_MODEL[ texcoordNum ];


	Model->VertexArray = new VERTEX_3D_MODEL[ vertexNum ];
	Model->VertexNum = vertexNum;

	Model->IndexArray = new unsigned int[ indexNum ];
	Model->IndexNum = indexNum;

	Model->SubsetArray = new SUBSET[ subsetNum ];
	Model->SubsetNum = subsetNum;




	//�v�f�Ǎ�
	VECTOR3D_MODEL *position = positionArray;
	VECTOR3D_MODEL *normal = normalArray;
	VECTOR2D_MODEL *texcoord = texcoordArray;

	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;


	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "mtllib" ) == 0 )
		{
			//�}�e���A���t�@�C��
			fscanf( file, "%s", str );

			char path[256];
			strcpy( path, dir );
			strcat( path, "\\" );
			strcat( path, str );

			LoadMaterial( path, &materialArray, &materialNum );
		}
		else if( strcmp( str, "o" ) == 0 )
		{
			//�I�u�W�F�N�g��
			fscanf( file, "%s", str );
		}
		else if( strcmp( str, "v" ) == 0 )
		{
			//���_���W
			fscanf( file, "%f", &position->x );
			fscanf( file, "%f", &position->y );
			fscanf( file, "%f", &position->z );
			position++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			//�@��
			fscanf( file, "%f", &normal->x );
			fscanf( file, "%f", &normal->y );
			fscanf( file, "%f", &normal->z );
			normal++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			//�e�N�X�`�����W
			fscanf( file, "%f", &texcoord->x );
			fscanf( file, "%f", &texcoord->y );
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			//�}�e���A��
			fscanf( file, "%s", str );

			if( sc != 0 )
				Model->SubsetArray[ sc - 1 ].IndexNum = ic - Model->SubsetArray[ sc - 1 ].StartIndex;

			Model->SubsetArray[ sc ].StartIndex = ic;


			for( unsigned int i = 0; i < materialNum; i++ )
			{
				if( strcmp( str, materialArray[i].Name ) == 0 )
				{
					Model->SubsetArray[ sc ].Material.Material = materialArray[i].Material;
					strcpy( Model->SubsetArray[ sc ].Material.TextureName, materialArray[i].TextureName );
					strcpy( Model->SubsetArray[ sc ].Material.Name, materialArray[i].Name );

					break;
				}
			}

			sc++;
			
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			//��
			in = 0;

			do
			{
				fscanf( file, "%s", str );

				s = strtok( str, "/" );	
				Model->VertexArray[vc].Position = positionArray[ atoi( s ) - 1 ];
				if( s[ strlen( s ) + 1 ] != '/' )
				{
					//�e�N�X�`�����W�����݂��Ȃ��ꍇ������
					s = strtok( NULL, "/" );
					Model->VertexArray[vc].TexCoord = texcoordArray[ atoi( s ) - 1 ];
				}
				s = strtok( NULL, "/" );	
				Model->VertexArray[vc].Normal = normalArray[ atoi( s ) - 1 ];

				Model->VertexArray[vc].Diffuse.r;
				Model->VertexArray[vc].Diffuse.g;
				Model->VertexArray[vc].Diffuse.b;
				Model->VertexArray[vc].Diffuse.a;

				Model->IndexArray[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c != '\r' );

			//�l�p�͎O�p�ɕ���
			if( in == 4 )
			{
				Model->IndexArray[ic] = vc - 4;
				ic++;
				Model->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}


	if( sc != 0 )
		Model->SubsetArray[ sc - 1 ].IndexNum = ic - Model->SubsetArray[ sc - 1 ].StartIndex;



	fclose(file);

	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}




//�}�e���A���ǂݍ���///////////////////////////////////////////////////////////////////
void CModel::LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum )
{

	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir);



	char str[256];

	FILE *file;
	file = fopen( FileName, "rt" );
	assert(file);

	MODEL_MATERIAL *materialArray;
	unsigned int materialNum = 0;

	//�v�f���J�E���g
	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;


		if( strcmp( str, "newmtl" ) == 0 )
		{
			materialNum++;
		}
	}


	//�������m��
	materialArray = new MODEL_MATERIAL[ materialNum ];


	//�v�f�Ǎ�
	int mc = -1;

	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;


		if( strcmp( str, "newmtl" ) == 0 )
		{
			//�}�e���A����
			mc++;
			fscanf( file, "%s", materialArray[ mc ].Name );
			strcpy( materialArray[ mc ].TextureName, "" );

			materialArray[mc].Material.Emission.r = 0.0f;
			materialArray[mc].Material.Emission.g = 0.0f;
			materialArray[mc].Material.Emission.b = 0.0f;
			materialArray[mc].Material.Emission.a = 0.0f;
		}
		else if( strcmp( str, "Ka" ) == 0 )
		{
			//�A���r�G���g
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.b );
			materialArray[ mc ].Material.Ambient.a = 1.0f;
		}
		else if( strcmp( str, "Kd" ) == 0 )
		{
			//�f�B�t���[�Y
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.b );
			materialArray[mc].Material.Diffuse.a = 1.0f;
					   
		}
		else if( strcmp( str, "Ks" ) == 0 )
		{
			//�X�y�L����
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.b );
			materialArray[ mc ].Material.Specular.a = 1.0f;
		}
		else if( strcmp( str, "Ns" ) == 0 )
		{
			//�X�y�L�������x
			fscanf( file, "%f", &materialArray[ mc ].Material.Shininess );
		}
		else if( strcmp( str, "d" ) == 0 )
		{
			//�A���t�@
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.a );
		}
		else if( strcmp( str, "map_Kd" ) == 0 )
		{
			//�e�N�X�`��
			fscanf( file, "%s", str );

			char path[256];
			strcpy( path, dir );
			strcat( path, "\\" );
			strcat( path, str );

			strcat( materialArray[ mc ].TextureName, path );
		}
	}


	*MaterialArray = materialArray;
	*MaterialNum = materialNum;
}

