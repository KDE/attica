# Attica

Open Collaboration Service client library

## Introduction

Attica is a Qt library that implements the Open Collaboration Services API version 1.6.
The REST API is defined here:
https://www.freedesktop.org/wiki/Specifications/open-collaboration-services/

It grants easy access to the services such as querying information about persons and contents.
The library is used in KNewStuff3 as content provider.
In order to integrate with KDE's Plasma Desktop, a platform plugin exists in [plasma-desktop](https://commits.kde.org/plasma-desktop?path=attica-kde).

Your basic entrypoint for using Attica's functionality is the Attica::ProviderManager class.
