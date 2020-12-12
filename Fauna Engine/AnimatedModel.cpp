/*#include "AnimatedModel.h"
#include <fstream>

using namespace DirectX;

bool AnimatedModel::Load(Graphics& gfx, std::wstring& filePath, std::vector<std::wstring>& texFilePaths)
{
    std::wifstream file(filePath.c_str());
    std::wstring contents;

    if (file.is_open())
    {
        while (file)
        {
            file >> contents;

            if (contents == L"MD5Version")
            {

            }
            else if (contents == L"commandline")
            {
                std::getline(file, contents);
            }
            else if (contents == L"numJoints")
            {
                file >> numJoints;
            }
            else if (contents == L"numMeshes")
            {
                file >> numMeshes;
            }
            else if (contents == L"joints")
            {
                Joint tempJoint;

                file >> contents;

                for (std::size_t i = 0; i < numJoints; i++)
                {
                    file >> tempJoint.name;//Store joint name
                    //check for spaces
                    if (tempJoint.name[tempJoint.name.size() - 1] != '"')
                    {
                        wchar_t tempChar;
                        bool jointNameFound = false;
                        while (!jointNameFound)
                        {
                            tempChar = file.get();

                            if (tempChar == '"')
                                jointNameFound = true;

                            tempJoint.name += tempChar;
                        }
                    }

                    file >> tempJoint.parentID;

                    file >> contents; //skip (
                    file >> tempJoint.pos.x >> tempJoint.pos.z >> tempJoint.pos.y;

                    file >> contents >> contents; //skip )(

                    file >> tempJoint.orientation.x >> tempJoint.orientation.z >> tempJoint.orientation.y;

                    tempJoint.name.erase(0, 1);

                    float t = 1.0f - (tempJoint.orientation.x * tempJoint.orientation.x)
                        - (tempJoint.orientation.y * tempJoint.orientation.y)
                        - (tempJoint.orientation.z * tempJoint.orientation.z);
                    if (t < 0.0f)
                    {
                        tempJoint.orientation.w = 0.0f;
                    }
                    else
                    {
                        tempJoint.orientation.w = -sqrtf(t);
                    }

                    std::getline(file, contents);// Skip rest of this line

                    joints.push_back(tempJoint);
                }

                file >> contents;
            }
            else if (contents == L"mesh")
            {
                Mesh tempMesh;
                int numVerts, numTris, numWeights;

                file >> contents;

                file >> contents;
                while (contents != L"}")
                {
                    if (contents == L"shader")
                    {
                        std::wstring fileNamePath;
                        file >> fileNamePath;

                        if (fileNamePath[fileNamePath.size() - 1] != '"')
                        {
                            wchar_t tempChar;
                            bool fileNameFound = false;
                            while (!fileNameFound)
                            {
                                tempChar = file.get();

                                if (tempChar == '"')
                                    fileNameFound = true;
                            
                                fileNamePath += tempChar;
                            }
                        }

                        fileNamePath.erase(0, 1);
                        fileNamePath.erase(fileNamePath.size() - 1, 1);

                        bool alreadyLoaded = false;
                        for (std::size_t i = 0; i < texFilePaths.size(); ++i)
                        {
                            if (fileNamePath == texFilePaths[i])
                            {
                                alreadyLoaded = true;
                                tempMesh.texArrayIndex = i;
                            }
                        }

                        if (!alreadyLoaded)
                        {
                            Texture tempTexture;
                            tempTexture.Load(gfx, fileNamePath.c_str());
                            textures.push_back(tempTexture);
                        }

                        std::getline(file, contents);
                    }
                    else if (contents == L"numverts")
                    {
                        file >> numVerts;//read in vertices count

                        std::getline(file, contents);

                        for (std::size_t i = 0; i < numVerts; i++)
                        {
                            VertexMD5 tempVert;

                            file >> contents >> contents >> contents;//skip vert # (

                            file >> tempVert.texCoord.x >> tempVert.texCoord.y;

                            file >> contents;

                            file >> tempVert.StartWeight;

                            file >> tempVert.WeightCount;

                            std::getline(file, contents);

                            tempMesh.vertices.push_back(tempVert);
                        }
                    }
                    else if (contents == L"numtris")
                    {
                        file >> numTris;
                        tempMesh.numTriangles = numTris;

                        std::getline(file, contents);

                        for (std::size_t i = 0; i < numTris; i++)//loop through each triangle
                        {
                            DWORD tempIndex;
                            file >> contents;//skip tri
                            file >> contents;//skip tri counter

                            for (std::size_t k = 0; k < 3; k++)//store the three verts
                            {
                                file >> tempIndex;
                                tempMesh.indices.push_back(tempIndex);
                            }

                            std::getline(file, contents);
                        }
                    }
                    else if (contents == L"numweights")
                    {
                        file >> numWeights;

                        std::getline(file, contents);//skip line

                        for (std::size_t i = 0; i < numWeights; i++)
                        {
                            Weight tempWeight;
                            file >> contents >> contents;//skip wieght #

                            file >> tempWeight.jointID;//store weight joint id

                            file >> tempWeight.bias;//store influence on vertex

                            file >> contents; // skip (

                            file >> tempWeight.pos.x//sotre weight local space
                                >> tempWeight.pos.z
                                >> tempWeight.pos.y;

                            std::getline(file, contents);

                            tempMesh.weights.push_back(tempWeight);
                        }
                    }
                    else
                        std::getline(file, contents);//skip anything else

                    file >> contents;//skip }
                }

                for (std::size_t i = 0; i < tempMesh.vertices.size(); ++i)
                {
                    VertexMD5 tempVert = tempMesh.vertices[i];
                    tempVert.pos = XMFLOAT3(0, 0, 0);

                    for (std::size_t j = 0; j < tempVert.WeightCount; ++j)
                    {
                        Weight tempWeight = tempMesh.weights[tempVert.StartWeight + j];
                        Joint tempJoint = joints[tempWeight.jointID];

                        XMVECTOR tempJointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
                        XMVECTOR tempWeightPos = XMVectorSet(tempWeight.pos.x, tempWeight.pos.y, tempWeight.pos.z, 0.0f);

                        XMVECTOR tempJointOrientationConjugate = XMVectorSet(-tempJoint.orientation.x, -tempJoint.orientation.y, -tempJoint.orientation.z, tempJoint.orientation.w);

                        XMFLOAT3 rotatedPoint;
                        XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightPos), tempJointOrientationConjugate));

                        tempVert.pos.x += (tempJoint.pos.x + rotatedPoint.x) * tempWeight.bias;
                        tempVert.pos.y += (tempJoint.pos.y + rotatedPoint.y) * tempWeight.bias;
                        tempVert.pos.z += (tempJoint.pos.z + rotatedPoint.z) * tempWeight.bias;
                    }

                    tempMesh.positions.push_back(tempVert.pos);

                }

                for (std::size_t i = 0; i < tempMesh.vertices.size(); i++)
                {
                    tempMesh.vertices[i].pos = tempMesh.positions[i];
                }

                //calculate normals using normal averaging
                std::vector<XMFLOAT3> tempNormal;

                XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

                float vecX, vecY, vecZ;

                XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
                XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

                //Compute face normals
                for (int i = 0; i < tempMesh.numTriangles; ++i)
                {
                    //Get the vector describing one edge of our triangle (edge 0,2)
                    vecX = tempMesh.vertices[tempMesh.indices[(i * 3)]].pos.x - tempMesh.vertices[tempMesh.indices[(i * 3) + 2]].pos.x;
                    vecY = tempMesh.vertices[tempMesh.indices[(i * 3)]].pos.y - tempMesh.vertices[tempMesh.indices[(i * 3) + 2]].pos.y;
                    vecZ = tempMesh.vertices[tempMesh.indices[(i * 3)]].pos.z - tempMesh.vertices[tempMesh.indices[(i * 3) + 2]].pos.z;
                    edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our first edge

                    //Get the vector describing another edge of our triangle (edge 2,1)
                    vecX = tempMesh.vertices[tempMesh.indices[(i * 3) + 2]].pos.x - tempMesh.vertices[tempMesh.indices[(i * 3) + 1]].pos.x;
                    vecY = tempMesh.vertices[tempMesh.indices[(i * 3) + 2]].pos.y - tempMesh.vertices[tempMesh.indices[(i * 3) + 1]].pos.y;
                    vecZ = tempMesh.vertices[tempMesh.indices[(i * 3) + 2]].pos.z - tempMesh.vertices[tempMesh.indices[(i * 3) + 1]].pos.z;
                    edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our second edge

                    //Cross multiply the two edge vectors to get the un-normalized face normal
                    XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));

                    tempNormal.push_back(unnormalized);
                }


                XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
                int facesUsing = 0;
                float tX, tY, tZ;

                for (int i = 0; i < tempMesh.vertices.size(); ++i)
                {
                    //Check which triangles use this vertex
                    for (int j = 0; j < tempMesh.numTriangles; ++j)
                    {
                        if (tempMesh.indices[j * 3] == i ||
                            tempMesh.indices[(j * 3) + 1] == i ||
                            tempMesh.indices[(j * 3) + 2] == i)
                        {
                            tX = XMVectorGetX(normalSum) + tempNormal[j].x;
                            tY = XMVectorGetY(normalSum) + tempNormal[j].y;
                            tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

                            normalSum = XMVectorSet(tX, tY, tZ, 0.0f);    //If a face is using the vertex, add the unormalized face normal to the normalSum

                            facesUsing++;
                        }
                    }

                    normalSum = normalSum / facesUsing;

                    normalSum = XMVector3Normalize(normalSum);

                    //Store the normal and tangent in our current vertex
                    tempMesh.vertices[i].normal.x = -XMVectorGetX(normalSum);
                    tempMesh.vertices[i].normal.y = -XMVectorGetY(normalSum);
                    tempMesh.vertices[i].normal.z = -XMVectorGetZ(normalSum);

                    //Clear normalSum, facesUsing for next vertex
                    normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
                    facesUsing = 0;
                }

                tempMesh.indexBuffer.Init(gfx, tempMesh.indices.data(), tempMesh.indices.size());

                tempMesh.vertexBuffer.Init(gfx, tempMesh.vertices.data(), tempMesh.vertices.size());

                //push back the tempMesh into the models subset vector
                //this->meshes.push_back(tempMesh);
            }
        }
    }
    else
    {
        return false;
    }

   // for (std::size_t i = 0; i < texFilePaths.size(); i++)
   // {
       // textures[i].load(pDevice, texFilePaths[i]);
   // }
    return true;
}

void AnimatedModel::Bind()
{
}

void AnimatedModel::Draw()
{
}

void AnimatedModel::Unbind()
{
}
*/