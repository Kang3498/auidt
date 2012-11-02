/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.eclipse.org/org/documents/epl-v10.php
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.ide.eclipse.auidt.internal.editors.manifest;


import com.android.ide.eclipse.auidt.internal.editors.AndroidSourceViewerConfig;

import org.eclipse.jface.text.contentassist.IContentAssistProcessor;
import org.eclipse.jface.text.source.ISourceViewer;

/**
 * Source Viewer Configuration that calls in ManifestContentAssist.
 */
public final class ManifestSourceViewerConfig extends AndroidSourceViewerConfig {

    private ManifestContentAssist mAndroidContentAssist;

    public ManifestSourceViewerConfig() {
        super();
        mAndroidContentAssist = new ManifestContentAssist();
    }

    @Override
    public IContentAssistProcessor getAndroidContentAssistProcessor(
            ISourceViewer sourceViewer,
            String partitionType) {
        return mAndroidContentAssist;
    }
}
