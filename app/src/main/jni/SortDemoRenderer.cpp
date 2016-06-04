//
// Created by matt on 5/20/16.
//

#include "SortDemoRenderer.h"
#include "SDShaders.h"
#include "SDMeshUtils.h"
#include <cmath>
#include <ctime>

SortDemoRenderer::SortDemoRenderer() {
    m_nWidth = 0;
    m_nHeight = 0;
}

SortDemoRenderer::~SortDemoRenderer() {

}

bool32 SortDemoRenderer::CreateRenderer(uint32 nWidth, uint32 nHeight) {
    m_nWidth = nWidth;
    m_nHeight = nHeight;

    m_nFrameNum = 0;

    SDPipeline::TPipelineInfo pipelineInfo = { SDShaders::VertexShader, SDShaders::FragmentShader };
    m_pipeline.Create(&pipelineInfo);
    m_pipeline.SetCulling(true);
    m_pipeline.SetCullFace(GL_CCW);
    m_pipeline.SetDepthValue(0.f);
    m_pipeline.SetDepthTest(true);

    m_fStartTime = time(NULL);
    m_fLastTime  = time(NULL);

    return true;
}

bool32 SortDemoRenderer::AddMesh(const char* pszBasePath, const char* pszMeshFile) {
    SDMesh::TMeshInfo meshInfo = {pszBasePath, pszMeshFile};
    SDMesh* pNewMesh = new SDMesh();
    bool32 bSuccess = pNewMesh->Create(&meshInfo);
    TMat4 mMvp = TMat4();
    mMvp.cX.x = 0.25f;
    mMvp.cY.y = 0.25f;
    mMvp.cZ.z = 0.25f;
    mMvp.cW.w = 1.f;
    pNewMesh->SetMVP(mMvp);
    m_meshStack.PushBack(pNewMesh);
    return bSuccess;
}

void   SortDemoRenderer::DrawFrame() {
    m_pipeline.Start();

    float fScale = /*0.0025**/fabs(sin(2.0*PI*SOFT_CAST(float, m_nFrameNum)/60.0));

    TMat4 mMvp = TMat4();
    mMvp.cX.x = fScale;
    mMvp.cY.y = fScale;
    mMvp.cZ.z = fScale;
    mMvp.cW.w = 1.f;

    for (uint32 nMesh = 0; nMesh < m_meshStack.GetNumElements(); ++nMesh) {
        SOFT_CAST(SDMesh*, m_meshStack.GetItem(nMesh))->SetMVP(mMvp);
        SOFT_CAST(SDMesh*, m_meshStack.GetItem(nMesh))->Draw();
    }

    m_pipeline.End();

    double fCurTime = time(NULL);
    if (fCurTime - m_fLastTime >= 1.f) {
        LOGI("%.2f FPS\n", SOFT_CAST(double, m_nFrameNum)/(fCurTime - m_fStartTime));
        m_fLastTime = fCurTime;
    }
    m_nFrameNum++;
}

void   SortDemoRenderer::DestroyRenderer() {
    m_pipeline.Destroy();
    uint32 nMeshCount = m_meshStack.GetNumElements();
    for (uint32 nMesh = 0; nMesh < nMeshCount; ++nMesh) {
        SOFT_CAST(SDMesh*, m_meshStack.GetBack())->Destroy();
        m_meshStack.RemoveBack();
    }
}

void SortDemoRenderer::UpdateViewport(uint32 nWidth, uint32 nHeight) {
    m_nWidth = nWidth;
    m_nHeight = nHeight;
}


SortDemoRenderer* pRenderer = NULL;

extern "C" {
    JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_create_1renderer(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_destroy_1renderer(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_draw_1frame(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_update_1viewport(JNIEnv * env, jobject obj,  jint width, jint height);
    //JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_add_1mesh(JNIEnv * env, jobject obj, const char* pszMeshFile);
};

JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_create_1renderer(JNIEnv * env, jobject obj,  jint width, jint height) {
    pRenderer = new SortDemoRenderer();
    pRenderer->CreateRenderer(width, height);
    //pRenderer->AddMesh("/sdcard/SortDemo/", "cube.obj");
    pRenderer->AddMesh("/sdcard/SortDemo/", "Sphere_2.obj");
    //pRenderer->AddMesh("/sdcard/SortDemo/", "DeathStarII.obj");
}

JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_destroy_1renderer(JNIEnv * env, jobject obj) {
    if (pRenderer != NULL) {
        pRenderer->DestroyRenderer();
        delete pRenderer;
        pRenderer = NULL;
    }
}

JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_draw_1frame(JNIEnv * env, jobject obj) {
    pRenderer->DrawFrame();
}

JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_update_1viewport(JNIEnv * env, jobject obj,  jint width, jint height) {
    pRenderer->UpdateViewport(width, height);
}



//JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_add_1mesh(JNIEnv * env, jobject obj, jstring pszMeshFile)
//{
//    const char* pszCMeshFile = (env)->GetStringUTFChars(pszMeshFile, NULL);
//    pRenderer->AddMesh(pszCMeshFile);
//}

