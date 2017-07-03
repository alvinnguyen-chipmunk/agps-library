#include "styl_agps_tmp.h"
#include "styl_agps_utils.h"

static gint waiting_scan = 0;
G_LOCK_DEFINE(waiting_scan);

//static NMClient *nm_client = NULL;
//static NMDevice *device    = NULL;
/* Global variables */
GMainLoop *loop = NULL; /* Main loo1p variable - needed for waiting for signal */

static void scan_done_cb(NMDeviceWifi *device, GError *error, gpointer user_data)
{
    DEBUG_0();
    if (error)
    {
        const char *text = "failed to scan";
        char *err_text = g_strdup_printf ("(%d) %s", error->code,
                                          error->message ? error->message : "Unknown error");

        g_warning ("%s: %s", text, err_text);
        g_free (err_text);
    }
    else
    {
        g_print("scan done\n");
    }

    DEBUG_0();

    sleep(1);

    g_main_loop_quit (loop);
//    G_UNLOCK(waiting_scan);
}

gint tmp_execute(GObject * nm_client)
{
    const GPtrArray *devices;
    NMDevice * nm_device = NULL;
    NMDevice * tmp   = NULL;

    devices = nm_client_get_devices (NM_CLIENT(nm_client));

    /* Go through the array and process Wi-Fi devices */
    for (gint i = 0; devices && (i < devices->len); i++)
    {
        tmp = g_ptr_array_index (devices, i);
        if (nm_device_get_state (tmp) == NM_DEVICE_STATE_ACTIVATED)
        {
            if (NM_IS_DEVICE_WIFI (tmp))
            {
                nm_device = tmp;
                break;
            }
        }
    }
    if(nm_device!=NULL)
    {
        DEBUG_0();
    //    G_LOCK(waiting_scan);
        nm_device_wifi_request_scan_simple(NM_DEVICE_WIFI (nm_device), scan_done_cb, NULL);
        DEBUG_0();
    //    G_LOCK(waiting_scan);
        DEBUG_0();
        loop = g_main_loop_new (NULL, FALSE);  /* Create main loop */
        DEBUG_0();
    //
        g_main_loop_run (loop);                /* Run main loop until scan done! */
        g_main_loop_unref (loop);

    //    G_LOCK(waiting_scan);
        DEBUG_0();
        return EXIT_SUCCESS;
    //    G_UNLOCK(waiting_scan);
    }

    return EXIT_FAILURE;
}

void tmp_free(GObject * nm_client)
{
    g_object_unref (nm_client);
}

GObject * tmp_init()
{
    NMClient * nm_client = NULL;
    NMDevice * nm_device = NULL;
    NMDevice * tmp   = NULL;

    const GPtrArray *devices;

    /* Get NMClient object */
    nm_client = nm_client_new ();
    if (!nm_client)
    {
        g_message ("Error: Could not create NMClient.");
        return NULL;
    }

    devices = nm_client_get_devices (nm_client);

    /* Go through the array and process Wi-Fi devices */
    for (gint i = 0; devices && (i < devices->len); i++)
    {
        tmp = g_ptr_array_index (devices, i);
        if (nm_device_get_state (tmp) == NM_DEVICE_STATE_ACTIVATED)
        {
            if (NM_IS_DEVICE_WIFI (tmp))
            {
                nm_device = tmp;
                break;
            }
        }
    }

    if(nm_device==NULL)
    {
        g_warning("The wifi device could not be found.");
        g_object_unref (nm_client);
        return NULL;
    }

    return (GObject *)nm_client;
}

// Change Log:
// 23 Apr 2013        Galen        Created
