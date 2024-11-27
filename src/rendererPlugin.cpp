#include "pch.h"
//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include <pxr/pxr.h>
#include "rendererPlugin.h"

#include <pxr/imaging/hdSt/renderDelegate.h>
#include <pxr/imaging/hd/rendererPluginRegistry.h>


PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    HdRendererPluginRegistry::Define<HdStormRendererPlugin>();
}

HdRenderDelegate *
HdStormRendererPlugin::CreateRenderDelegate()
{
    return new HdStRenderDelegate();
}

HdRenderDelegate*
HdStormRendererPlugin::CreateRenderDelegate(
    HdRenderSettingsMap const& settingsMap)
{
    return new HdStRenderDelegate(settingsMap);
}

void
HdStormRendererPlugin::DeleteRenderDelegate(HdRenderDelegate *renderDelegate)
{
    delete renderDelegate;
}

bool
HdStormRendererPlugin::IsSupported(bool gpuEnabled) const
{
    const bool support = gpuEnabled && HdStRenderDelegate::IsSupported();
    if (!support) {
        TF_DEBUG(HD_RENDERER_PLUGIN).Msg(
            "hdStorm renderer plugin unsupported: %s\n",
            gpuEnabled ? "hgi unsupported" : "no gpu");
    }
    return support;
}


PXR_NAMESPACE_CLOSE_SCOPE



#include <iostream>

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

int main( int argc, char* argv[] )
{
    try
    {
        NS::SharedPtr<NS::AutoreleasePool> pAutoreleasePool = NS::TransferPtr(NS::AutoreleasePool::alloc()->init());

        NS::SharedPtr<CA::MetalLayer>metalLayer = NS::TransferPtr(CA::MetalLayer::layer());
        // metalLayer->setPixelFormat(MTL::PixelFormatbrg)
        // std::cout << metalLayer->pixelFormat() << std::endl;

        NS::SharedPtr<MTL::Device> device = NS::TransferPtr(MTL::CreateSystemDefaultDevice());
        NS::SharedPtr<MTL::CommandQueue> commandQueue = NS::TransferPtr(device->newCommandQueue());
        metalLayer->setDevice(device.get());

        // Draw
        {
            NS::SharedPtr<MTL::CommandBuffer> commandBuffer = NS::TransferPtr(commandQueue->commandBuffer());
            NS::SharedPtr<MTL::RenderPassDescriptor> renderPassDescriptor = NS::TransferPtr(MTL::RenderPassDescriptor::alloc()->init());
            NS::SharedPtr<MTL::RenderCommandEncoder> renderCommandEncoder = NS::TransferPtr(commandBuffer->renderCommandEncoder(renderPassDescriptor.get()));
            renderCommandEncoder->endEncoding();
            commandBuffer->presentDrawable( metalLayer->nextDrawable() );
            commandBuffer->commit();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    


    return 0;
}
