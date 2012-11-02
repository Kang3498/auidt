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

package com.android.ide.eclipse.auidt.internal.editors.layout;

import com.android.annotations.VisibleForTesting;
import com.android.ide.eclipse.auidt.internal.editors.AndroidContentAssist;
import com.android.ide.eclipse.auidt.internal.editors.descriptors.ElementDescriptor;
import com.android.ide.eclipse.auidt.internal.sdk.AndroidTargetData;

import org.w3c.dom.Node;

/**
 * Content Assist Processor for /res/layout XML files
 */
@VisibleForTesting
public final class LayoutContentAssist extends AndroidContentAssist {

    /**
     * Constructor for LayoutContentAssist
     */
    public LayoutContentAssist() {
        super(AndroidTargetData.DESCRIPTOR_LAYOUT);
    }

    @Override
    protected Object[] getChoicesForElement(String parent, Node currentNode) {
        Object[] choices = super.getChoicesForElement(parent, currentNode);
        if (choices == null) {
            if (currentNode.getParentNode().getNodeType() == Node.ELEMENT_NODE) {
                String parentName = currentNode.getParentNode().getNodeName();
                if (parentName.indexOf('.') != -1) {
                    // Custom view with unknown children; just use the root descriptor
                    // to get all eligible views instead
                    ElementDescriptor[] children = getRootDescriptor().getChildren();
                    for (ElementDescriptor e : children) {
                        if (e.getXmlName().startsWith(parent)) {
                            return sort(children);
                        }
                    }
                }
            }
        }

        return choices;
    }
}