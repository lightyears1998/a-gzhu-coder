# Fragment笔记

## 生命周期

- `onAttach(Activity)` 与一个Activity相关联，`getActivity()`
- `onCreate(Bundle)`
- `onCreateView(Layoutinflater, ViewGroup, Bundle)` 返回与Fragment相关的View
- `onActivityCreated(Bundle)`
- `onViewStateResourced(Bundle)` Fragment其View层次的所有保存状态都已恢复时触发
- `onStart()` 触发同步Activity
- `onResume()` 触发同步Activity
- `onPause()` 触发同步
- `onStop()` 触发同步
- `onDestroyView()` 触发同步
- `onDestroy` 触发同步
- `onDetach()` 此时调用`getActivity()`返回空值，确保与Activity没有任何关联

## 给予Fragment数据

Fragment可以保存和恢复状态，需要一个默认的构造器；可以使一个Fragment与Activity相关联之前，通过静态`newInstance()`建立一个Fragment的自变量

示例：传递一个参数给fragment，并在创建View时使用

```java
public class TextViewFragment extends Fragment {
    private static final String KEY_TEXY = "text";

    public static TextViewFragment newInstance(String text) {
        TextViewFragment f = new TextViewFragment();

        Budle args = new Bundle();
        args.putString(KEY_TEXT, text);
        f.setArguments(args);

        return f;
    }

    public String getText() {
        return getArguments().getString(KEY_TEXT);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstatanceState) {
        TextView tv = new TextView(getActivity());
        tv.setText(getText());
        return tv;
    }
}

```

通过调用`setRetainInstance(true)`方法可以在Activity重建时仍然保留Fragment，这样就不用`onDestroy()`和`onCreate()`了。

## 与Activity通讯

示例：简单的DialogFragment

```java
public class SampleDialogFragment extends DialogFragment {
    public interface OnDialogChoiceListener {
        public void onDialogCanceled();
        public void onDialogConfirmed();
    }

    private static final String ARG_CONTENT_RESOURCE_ID = "contentResourceId";
    private static final String ARG_CONFIRM_RESOURCE_ID = "confirmResourceId";

    private int mContentResourceId;
    private int mConfirmResourceId;

    private onDialogChoiceListener mListener;

    public static SampleDialogFragment newInstance(int contentResourceId, int confirmResourceId) {
        SampleDialogFragment dialog = new SampleDialogFragment();
        Bundle args = new Bundle();
        args.putInt(ARG_CONTENT_RESOURCE_ID, contentResourceId);
        args.putInt(ARG_CONFIRM_RESOURCE_ID, confirmResourceId);
        fragment.setArguments(args);
        return dialog;
    }

    public SampleDialogFragment {
        // 必须是空的公共构造器
    }

    @Override
    public void static onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        final Bundle args = getArguments();
        if (args == null) {
            throw new IlleagalStateException("No arguments set, use the "
                + " newInstance method to construct this fragment");
        }
        mContentResourceId = args.getInt(ARG_CONTENT_RESOURCE_ID);
        mConfirmResourceId = args.getInt(ARG_CONFIRM_RESOURCE_ID);
    }

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setMessage(mContentResourceId);
            .setPositiveButton(mConfirmResourceId, new DialogInterface.OnClickListener() {
                public void OnClick(DialogInterface dialog, int id) {
                    mListener.onDialogConfirmed();
                }
            })
            .setNavigationButton(R.string.cancel, new DialogInterface.OnClickListener() {
                public void OnClick(DialogInterface dialog, int id) {
                    mListener.onDialogCanceled();
                }
            })
        return builder.create();
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttch(activity);
        try {
            mListener = (OnDialogChoiceListener) activity;
        } catch (ClassException e) {
            throw new ClassCastException(activity.toString(), " must implement OnFragmentInteractionListener");
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }
}
```

## 执行Fragment事务

```java
getSupportFragmentManager().beginTransaction()
    .add(R.id.container, ExampleFragment.newInstance())
    .addToBackStack(null)
    .commit();
```